#include "global.h"
#include "ast.h"

int print_pipeline_node(struct s_pipeline_node *node, FILE* dot, int n)
{
    fprintf(dot, "%i [label=pipeline];\n", n);
    int m = n;
    if (node == NULL)
        return n + 1;
    if (node->commands != NULL)
    {
        for (int i = 0; i < node->nb_commands; i++)
        {
            fprintf(dot, "%i -> %i;\n", n, m + 1);
            m = print_ast_node(node->commands[i], dot, m + 1);
        }
    }
    return m + 1;
}

int print_and_or_node(struct s_and_or_node *node, FILE* dot, int n)
{
    if (node == NULL)
        return n + 1;
    int m = n;
    if (node->type == ANDOR_NONE)
        fprintf(dot, "%i [label=\"and_or (None)\"];\n", n);
    else if (node->type == ANDOR_OR)
        fprintf(dot, "%i [label=\"and_or (||)\"];\n", n);
    else if (node->type == ANDOR_AND)
        fprintf(dot, "%i [label=\"and_or (&&)\"];\n", n);
    if (node->left != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->left, dot, m + 1);
    }
    if (node->right != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->right, dot, m + 1);
    }
    return m + 1;
}

int print_list_node(struct s_list_node *node, FILE* dot, int n)
{
    if (node == NULL)
        return n + 1;
    int m = n;
    if (node->type == LIST_NONE)
        fprintf(dot, "%i [label=\"list (None)\"];\n", n);
    else if (node->type == LIST_AND)
        fprintf(dot, "%i [label=\"list (&)\"];\n", n);
    else if (node->type == LIST_SEMI)
        fprintf(dot, "%i [label=\"list (;)\"];\n", n);
    else if (node->type == LIST_BG)
        fprintf(dot, "%i [label=\"list (BG)\"];\n", n);
    if (node->left != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->left, dot, m + 1);
    }
    if (node->right != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->right, dot, m + 1);
    }
    return m + 1;
}

