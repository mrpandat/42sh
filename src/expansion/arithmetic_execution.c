#include <expansion.h>
#include "../includes/expansion.h"
#include "../includes/util.h"
#include "../includes/global.h"

static int execute_binop_node(struct s_binop_node *node)
{
    if (node->type == AL_MINUS)
        return execute_art_node(node->left) - execute_art_node(node->right);
    else if (node->type == AL_PLUS)
        return execute_art_node(node->left) + execute_art_node(node->right);
    else if (node->type == AL_MULT)
        return execute_art_node(node->left) * execute_art_node(node->right);
    else if (node->type == AL_DIV)
        return execute_art_node(node->left) / execute_art_node(node->right);
    else if (node->type == AL_POW)
        return my_pow(execute_art_node(node->left),
                      execute_art_node(node->right));
    else if (node->type == AL_BW_AND)
        return execute_art_node(node->left) & execute_art_node(node->right);
    else if (node->type == AL_BW_OR)
        return execute_art_node(node->left) | execute_art_node(node->right);
    else if (node->type == AL_BW_XOR)
        return execute_art_node(node->left) ^ execute_art_node(node->right);
    else if (node->type == AL_LG_AND)
        return execute_art_node(node->left) != 0
               && execute_art_node(node->right) != 0;
    else if (node->type == AL_LG_OR)
        return execute_art_node(node->left) != 0
               || execute_art_node(node->right) != 0;
    else
        return 42;
}

static int execute_unop_node(struct s_unop_node *node)
{
    if (node->type == AL_UNARY_MINUS)
        return -execute_art_node(node->number);
    else if (node->type == AL_UNARY_PLUS)
        return +execute_art_node(node->number);
    else if (node->type == AL_LG_NEG)
        return !execute_art_node(node->number);
    else if (node->type == AL_BW_NEG)
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
        {
            int res = atoi(get_var(node->data.number->data.variable));
            return res;
        }
    }
    else if (node->type == ART_BINOP)
        return execute_binop_node(node->data.binop);
    else if (node->type == ART_UNOP)
        return execute_unop_node(node->data.unop);
    else
        return 42;
}

