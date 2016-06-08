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
    int ht_size = ht_size(ht);

    if (0 == ht_size)
        return NULL;

    if (NULL == (elements = malloc(ht_size * sizeof (struct s_element *))))
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

    int ht_size = ht_size(ht);

    if (0 == ht_size)
        return;

    for (size_t i = 0; i < ht->size; ++i)
    {
        if (NULL == ht->table[i])
            continue;

        struct s_element *list = ht->table[i];

        while (NULL != list)
        {
            struct s_element *tmp = list;
            list = list->next;
            ht_free_element(ht, tmp);
        }
    }
}

