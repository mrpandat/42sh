#define _GNU_SOURCE

#include "../includes/hashtable.h"

static void insert_new_element(struct s_hashtable *ht, struct s_element *prev,
                               char *key, void *value)
{
    size_t index = ht_hash(ht, key);
    struct s_element *curr = NULL;

    if (NULL == prev)
        curr = prev;
    else
        curr = prev->next;

    struct s_element *new_element = ht_new_element(key, value);

    if (curr == ht->table[index])
    {
        new_element->next = curr;
        ht->table[index] = new_element;
    }
    else if (NULL != prev && NULL == curr)
        prev->next = new_element;
    else
    {
        new_element->next = curr;
        prev->next = new_element;
    }
}

void ht_insert(struct s_hashtable *ht, char *key, void *value)
{
    size_t index = ht_hash(ht, key);

    struct s_element *curr = ht->table[index];
    struct s_element *prev = NULL;

    while (NULL != curr && NULL != curr->key && strcmp(key, curr->key) > 0)
    {
        prev = curr;
        curr = curr->next;
    }

    if (NULL != curr && NULL != curr->key && 0 == strcmp(key, curr->key))
    {
        free(curr->value);
        curr->value = strdup(value);
    }
    else
        insert_new_element(ht, prev, key, value);
}

void ht_remove(struct s_hashtable *ht, char *key)
{
    size_t index = ht_hash(ht, key);

    struct s_element *curr = ht->table[index];
    struct s_element *prev = NULL;

    while (NULL != curr && NULL != curr->key && strcmp(key, curr->key) > 0)
    {
        prev = curr;
        curr = curr->next;
    }

    if (NULL != curr && NULL != curr->key && 0 == strcmp(key, curr->key))
    {
        if (NULL != prev)
            prev->next = curr->next;
        else
            ht->table[index] = curr->next;

        ht_free_element(ht, curr);
    }
}

struct s_element *ht_get(struct s_hashtable *ht, char *key)
{
    size_t index = ht_hash(ht, key);

    struct s_element *curr = ht->table[index];

    while (NULL != curr && NULL != curr->key && strcmp(key, curr->key) > 0)
        curr = curr->next;

    if (NULL != curr && NULL != curr->key && 0 == strcmp(key, curr->key))
        return curr;

    return NULL;
}

void free_element_value(void *value)
{
    free(value);
}
