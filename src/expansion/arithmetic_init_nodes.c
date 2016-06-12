#define _GNU_SOURCE

#include "../includes/global.h"
#include "../includes/expansion.h"
#include "../includes/util.h"

struct s_art_node *init_art_node()
{
    return malloc(sizeof (struct s_art_node));
}

struct s_binop_node *init_binop_node(struct s_art_node *left,
                                     enum e_binop_type type,
                                     struct s_art_node *right)
{
    struct s_binop_node *node = malloc(sizeof (struct s_binop_node));
    node->left = left;
    node->type = type;
    node->right = right;
    return node;
}

struct s_unop_node *init_unop_node(enum e_unop_type type,
                                   struct s_art_node *son)
{
    struct s_unop_node *node = malloc(sizeof (struct s_unop_node));
    node->type = type;
    node->number = son;
    return node;
}

struct s_number_node *init_num_node_int(int num)
{
    struct s_number_node *node = malloc(sizeof (struct s_number_node));
    node->type = NUM_INT;
    node->data.integer = num;
    return node;
}
