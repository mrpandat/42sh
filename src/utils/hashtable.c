#include "../includes/hashtable.h"

struct s_hashtable *ht_init(size_t size, void (*destroy_val_fn)(void *))
{
    struct s_hashtable *ht = NULL;

    if (size < 1)
        return NULL;

    if (NULL == (ht = malloc(sizeof (struct s_hashtable))))
        return NULL;

    if (NULL == (ht->table = malloc(size * sizeof (struct s_element *))))
    {
        free(ht);
        return NULL;
    }

    for (size_t i = 0; i < size; ++i)
    {
        ht->table[i] = NULL;
    }

    ht->size = size;
    ht->destroy_val_fn = destroy_val_fn;
    return ht;
}

size_t ht_hash(struct s_hashtable *ht, char *key)
{
    size_t hashval = 0;
    size_t i = 0;

    while (i < strlen(key))
    {
        hashval = hashval << 8;
        hashval += key[i];
        i++;
    }

    return hashval % ht->size;
}

static void ht_free_list(struct s_hashtable *ht, struct s_element *list)
{
    if (NULL == list)
        return;

    struct s_element *tmp = list;
    while (NULL != list)
    {
        tmp = list;
        list = list->next;
        ht_free_element(ht, tmp);
    }
}

void ht_destroy(struct s_hashtable *ht)
{
    if (NULL == ht || NULL == ht->table)
        return;

    /** Free element lists */
    for (size_t i = 0; i < ht->size; ++i)
    {
        ht_free_list(ht, ht->table[i]);
    }

    /** Free structure */
    free(ht->table);
    free(ht);
}
