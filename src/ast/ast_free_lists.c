#include "global.h"
#include "ast.h"

void free_pipeline_node(struct s_pipeline_node *node)
{

    if (node == NULL)
        return;
    if (node->commands != NULL)
    {
        for (int i = 0; i < node->nb_commands; i++)
            free_ast_node(node->commands[i]);
        free(node->commands);
    }
    free(node);
}

void free_and_or_node(struct s_and_or_node *node)
{
    if (node == NULL)
        return;
    if (node->left != NULL)
        free_ast_node(node->left);
    if (node->right != NULL)
        free_ast_node(node->right);
    free(node);
}

void free_list_node(struct s_list_node *node)
{
    if (node == NULL)
        return;
    if (node->left != NULL)
        free_ast_node(node->left);
    if (node->right != NULL)
        free_ast_node(node->right);
    free(node);
}

