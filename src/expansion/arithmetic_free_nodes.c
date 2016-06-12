#define _GNU_SOURCE

#include "../includes/global.h"
#include "../includes/expansion.h"
#include "../includes/util.h"

void free_binop_node(struct s_binop_node *node)
{
    free_art_node(node->left);
    free_art_node(node->right);
    free(node);
}

void free_unop_node(struct s_unop_node *node)
{
    free_art_node(node->number);
    free(node);
}

void free_num_node(struct s_number_node *node)
{
    free(node);
    return;
}

void free_art_node(struct s_art_node *node)
{
    if (node->type == ART_NUM)
        free_num_node(node->data.number);
    else if (node->type == ART_BINOP)
        free_binop_node(node->data.binop);
    else if (node->type == ART_UNOP)
        free_unop_node(node->data.unop);
    free(node);
}
