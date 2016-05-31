#include "global.h"
#include "ast.h"

void free_if_node(struct s_if_node *node)
{
    if (node == NULL)
        return;
    if (node->predicate != NULL)
        free_ast_node(node->predicate);
    if (node->true_statement != NULL)
        free_ast_node(node->true_statement);
    if (node->false_statement != NULL)
        free_ast_node(node->false_statement);
    free(node);
}

void free_case_node(struct s_case_node *node)
{
    if (node == NULL)
        return;
    if (node->items != NULL)
    {
        for (int i = 0; i < node->nb_items; i++)
            free_case_item_node(node->items[i]);
        free(node->items);
    }
    free(node);
}

void free_case_item_node(struct s_case_item_node *node)
{

    if (node == NULL)
        return;
    if (node->words != NULL)
    {
        for (int i = 0; i < node->nb_words; i++)
            free(node->words[i]);
        free(node->words);
    }
    free(node);
}
