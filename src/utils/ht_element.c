#define _GNU_SOURCE

#include "../includes/hashtable.h"

struct s_element *ht_new_element(char *key, void *value)
{
    struct s_element *element;

    if (NULL == (element = malloc(sizeof (struct s_element))))
    {
        return NULL;
    }

    if (NULL == (element->key = strdup(key)))
    {
        free(element);
        return NULL;
    }

    if (NULL == (element->value = strdup(value)))
    {
        free(element->key);
        free(element);
        return NULL;
    }

    element->next = NULL;
    return element;
}

void ht_free_element(struct s_hashtable *ht, struct s_element *element)
{
    if (NULL == element)
        return;

    (*ht->destroy_val_fn)(element->value);
    free(element->key);
    free(element);
}

