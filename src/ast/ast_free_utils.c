#include "global.h"
#include "ast.h"

static void free_loops_control_nodes(struct s_ast_node *node)
{
    enum e_node_type type = node->type;
    if (type == ND_IF)
        free_if_node(node->data.s_if_node);
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
}

void free_ast_node(struct s_ast_node *node)
{
    enum e_node_type type = node->type;
    if (type == ND_COMMAND)
        free_command_node(node->data.s_command_node);
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
    else
        free_loops_control_nodes(node);
    free(node);
    return;
}

void free_redirection_node(struct s_redirection_node *node)
{
    if (node == NULL)
        return;
    free(node);
}
