#include "global.h"
#include "ast.h"

void free_while_node(struct s_while_node *node)
{
    if (node == NULL)
        return;
    if (node->predicate != NULL)
        free_ast_node(node->predicate);
    if (node->statement != NULL)
        free_ast_node(node->statement);
    free(node);
}

void free_until_node(struct s_until_node *node)
{
    if (node == NULL)
        return;
    if (node->predicate != NULL)
        free_ast_node(node->predicate);
    if (node->statement != NULL)
        free_ast_node(node->statement);
    free(node);
}

void free_for_node(struct s_for_node *node)
{
    if (node == NULL)
        return;
    if (node->do_group != NULL)
        free_ast_node(node->do_group);
    if (node->words != NULL)
    {
        for (int i = 0; i < node->nb_words; i++)
            free_word(node->words[i]);
        free(node->words);
    }
    free(node);
}
