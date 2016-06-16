#include "global.h"
#include "ast.h"

static int print_loops_control_nodes(struct s_ast_node *node, FILE* dot, int n)
{
    enum e_node_type type = node->type;
    if (type == ND_IF)
        return print_if_node(node->data.s_if_node, dot, n);
    else if (type == ND_WHILE)
        return print_while_node(node->data.s_while_node, dot, n);
    else if (type == ND_UNTIL)
        return print_until_node(node->data.s_until_node, dot, n);
    else if (type == ND_CASE)
        return print_case_node(node->data.s_case_node, dot, n);
    else if (type == ND_CASE_ITEM)
        return print_case_item_node(node->data.s_case_item_node, dot, n);
    else if (type == ND_FOR)
        return print_for_node(node->data.s_for_node, dot, n);
    else
        return n + 1;
}

int print_ast_node(struct s_ast_node *node, FILE* dot, int n)
{
    enum e_node_type type = node->type;
    if (type == ND_COMMAND)
        return print_command_node(node->data.s_command_node, dot, n);
    else if (type == ND_FUNCDEC)
        return print_funcdec_node(node->data.s_funcdec_node, dot, n);
    else if (type == ND_SIMPLE_COMMAND)
        return print_simple_command_node(node->data.s_simple_command_node,
                                         dot,
                                         n);
    else if (type == ND_PIPELINE)
        return print_pipeline_node(node->data.s_pipeline_node, dot, n);
    else if (type == ND_AND_OR)
        return print_and_or_node(node->data.s_and_or_node, dot, n);
    else if (type == ND_LIST)
        return print_list_node(node->data.s_list_node, dot, n);
    else
        return print_loops_control_nodes(node, dot, n);
}

void print_ast(struct s_ast_node *root)
{
    FILE *dot;
    dot = fopen("./ast.dot", "w");
    if (dot != NULL)
    {
        fprintf(dot, "digraph G {\n");
        print_ast_node(root, dot, 0);
        fprintf(dot, "}\n");
        fclose(dot);
    }
    else
        fprintf(stderr, "Impossible to write ast.dot file");
}
