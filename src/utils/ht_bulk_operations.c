#define _GNU_SOURCE

#include "../includes/hashtable.h"

int ht_size(struct s_hashtable *ht)
{
    if (NULL == ht)
        return 0;

    int size = 0;

    for (size_t i = 0; i < ht->size; ++i)
    {
        if (NULL == ht->table[i])
            continue;

        struct s_element *list = ht->table[i];

        while (NULL != list)
        {
            size++;
            list = list->next;
        }
    }

    return size;
}

struct s_element **ht_get_all(struct s_hashtable *ht)
{
    if (NULL == ht)
        return NULL;

    struct s_element **elements;
    int htsize = ht_size(ht);

    if (0 == htsize)
        return NULL;

    if (NULL == (elements = malloc(htsize * sizeof (struct s_element *))))
        return NULL;

    int size = 0;
    for (size_t i = 0; i < ht->size; ++i)
    {
        if (NULL == ht->table[i])
            continue;

        struct s_element *list = ht->table[i];

        while (NULL != list)
        {
            elements[size] = list;
            size++;
            list = list->next;
        }
    }

    return elements;
}

void ht_remove_all(struct s_hashtable *ht)
{
    if (NULL == ht)
        return;

    int htsize = ht_size(ht);

    if (0 == htsize)
        return;

    for (size_t i = 0; i < ht->size; ++i)
    {
        ht_free_list(ht, ht->table[i]);
        ht->table[i] = NULL;
    }
}

