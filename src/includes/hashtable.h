#ifndef HASHTABLE_H
# define HASHTABLE_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <assert.h>

struct s_element
{
    char *key;
    void *value;
    struct s_element *next;
};

struct s_hashtable
{
    size_t size;
    struct s_element **table;

    void (*destroy_val_fn)(void *);
};

/* File: hashtable.c */

struct s_hashtable *ht_init(size_t size, void (*destroy_val_fn)(void *));

size_t ht_hash(struct s_hashtable *ht, char *key);

void ht_destroy(struct s_hashtable *ht);

/* File: ht_element.c */

struct s_element *ht_new_element(char *key, void *value);

void ht_free_element(struct s_hashtable *ht, struct s_element *element);

/* File: ht_operations.c */

void ht_insert(struct s_hashtable *ht, char *key, void *value);

void ht_remove(struct s_hashtable *ht, char *key);

struct s_element *ht_get(struct s_hashtable *ht, char *key);

// For testing purposes
void free_element_value(void *value);

#endif /* !HASHTABLE_H */
