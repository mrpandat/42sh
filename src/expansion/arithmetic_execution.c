#include "../includes/expansion.h"
#include "../includes/util.h"
#include "../includes/global.h"

static int execute_binop_node(struct s_binop_node *node)
{
    if (node->type == BINOP_MINUS)
        return execute_art_node(node->left) - execute_art_node(node->right);
    else if (node->type == BINOP_ADD)
        return execute_art_node(node->left) + execute_art_node(node->right);
    else if (node->type == BINOP_MULT)
        return execute_art_node(node->left) * execute_art_node(node->right);
    else if (node->type == BINOP_DIV)
        return execute_art_node(node->left) / execute_art_node(node->right);
    else if (node->type == BINOP_POW)
        return my_pow(execute_art_node(node->left), execute_art_node
                (node->right));
    else if (node->type == BINOP_BIT_AND)
        return execute_art_node(node->left) & execute_art_node(node->right);
    else if (node->type == BINOP_BIT_OR)
        return execute_art_node(node->left) | execute_art_node(node->right);
    else if (node->type == BINOP_BIT_XOR)
        return execute_art_node(node->left) ^ execute_art_node(node->right);
    else if (node->type == BINOP_BOOL_AND)
        return execute_art_node(node->left) && execute_art_node(node->right);
    else if (node->type == BINOP_BOOL_OR)
        return execute_art_node(node->left) || execute_art_node(node->right);
    else
        return 42;
}

static int execute_unop_node(struct s_unop_node *node)
{
    if (node->type == UNOP_MINUS)
        return -execute_art_node(node->number);
    else if (node->type == UNOP_ADD)
        return +execute_art_node(node->number);
    else if (node->type == UNOP_BANG)
        return !execute_art_node(node->number);
    else if (node->type == UNOP_INV)
        return ~execute_art_node(node->number);
    else
        return 42;
}


int execute_art_node(struct s_art_node *node)
{
    if (node->type == ART_NUM)
    {
        if (node->data.number->type == NUM_INT)
            return node->data.number->data.integer;
        else
            return 42;
    }
    else if (node->type == ART_BINOP)
        return execute_binop_node(node->data.binop);
    else if (node->type == ART_UNOP)
        return execute_unop_node(node->data.unop);
    else
        return 42;
}

