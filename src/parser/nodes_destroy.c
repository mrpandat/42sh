#include "../includes/global.h"
#include "../includes/ast.h"

void free_ast_node(struct s_ast_node *node)
{
    enum e_node_type type = node->type;
    if (type == ND_IF)
        free_if_node(node->data.s_if_node);
    else if (type == ND_COMMAND)
        free_command_node(node->data.s_command_node);
    else if (type == ND_WHILE)
        free_while_node(node->data.s_while_node);
    else if (type == ND_UNTIL)
        free_until_node(node->data.s_until_node);
    else if (type == ND_CASE)
        free_case_node(node->data.s_case_node);
    else if (type == ND_CASE_ITEM)
        free_case_item_node(node->data.s_case_item_node);
    else if (type == ND_FOR)
        free_for_node(node->data.s_for_node);
    else if (type == ND_REDIRECTION)
        free_redirection_node(node->data.s_redirection_node);
    else if (type == ND_FUNCDEC)
        free_funcdec_node(node->data.s_funcdec_node);
    else if (type == ND_SIMPLE_COMMAND)
        free_simple_command_node(node->data.s_simple_command_node);
    else if (type == ND_PIPELINE)
        free_pipeline_node(node->data.s_pipeline_node);
    else if (type == ND_AND_OR)
        free_and_or_node(node->data.s_and_or_node);
    else if (type == ND_LIST)
        free_list_node(node->data.s_list_node);
    free(node);
    return;
}

void free_if_node(struct s_if_node *node)
{
    if (node == NULL)
        return;
    free(node);
}
void free_while_node(struct s_while_node *node)
{
    if (node == NULL)
        return;
    free(node);
}
void free_until_node(struct s_until_node *node)
{
    if (node == NULL)
        return;
    free(node);
}
void free_case_node(struct s_case_node *node)
{
    if (node == NULL)
        return;
    for (int i = 0; i < node->nb_items; i++)
        free(node->items[i]);
    free(node);
}
void free_case_item_node(struct s_case_item_node *node)
{

    if (node == NULL)
        return;
    for (int i = 0; i < node->nb_words; i++)
        free(node->words[i]);
    free(node);
}
void free_for_node(struct s_for_node *node)
{
    if (node == NULL)
        return;
    for (int i = 0; i < node->nb_words; i++)
        free(node->words[i]);
    free(node);
}
void free_redirection_node(struct s_redirection_node *node)
{
    if (node == NULL)
        return;
    free(node);
}
void free_funcdec_node(struct s_funcdec_node *node)
{
    if (node == NULL)
        return;
    free(node);
}
void free_simple_command_node(struct s_simple_command_node *node)
{
    if (node == NULL)
        return;
    for (int i = 0; i < node->nb_elements; i++)
        free(node->elements[i]);
    free(node);
}

void free_command_node(struct s_command_node *node)
{
    if (node == NULL)
        return;
    for (int i = 0; i < node->nb_redirections; i++)
        free(node->redirections[i]);
    free(node);
}
void free_pipeline_node(struct s_pipeline_node *node)
{

    if (node == NULL)
        return;
    for (int i = 0; i < node->nb_commands; i++)
        free(node->commands[i]);
    free(node);
}
void free_and_or_node(struct s_and_or_node *node)
{
    if (node == NULL)
        return;
    free(node);
}
void free_list_node(struct s_list_node *node)
{
    if (node == NULL)
        return;
    free(node);
}