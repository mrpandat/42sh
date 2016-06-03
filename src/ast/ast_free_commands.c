#include "global.h"
#include "ast.h"

void free_simple_command_node(struct s_simple_command_node *node)
{
    if (node == NULL)
        return;
    if (node->elements != NULL)
    {
        for (int i = 0; i < node->nb_elements; i++)
            free_element_node(node->elements[i]);
        free(node->elements);
    }
    free(node);
}

void free_command_node(struct s_command_node *node)
{
    if (node == NULL)
        return;
    if (node->content != NULL)
        free_ast_node(node->content);
    for (int i = 0; i < node->nb_redirections; i++)
        free_redirection_node(node->redirections[i]);
    free(node);
}

void free_funcdec_node(struct s_funcdec_node *node)
{
    if (node == NULL)
        return;
    if (node->shell_command != NULL)
        free_ast_node(node->shell_command);
    free(node);
}
