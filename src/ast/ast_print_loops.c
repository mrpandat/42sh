#include "global.h"
#include "ast.h"

int print_while_node(struct s_while_node *node, FILE* dot, int n)
{
    fprintf(dot, "%i [label=while];\n", n);
    int m = n;
    if (node == NULL)
        return m + 1;
    if (node->predicate != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->predicate, dot, m + 1);
    }
    if (node->statement != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->statement, dot, m + 1);
    }
    return m + 1;
}

int print_until_node(struct s_until_node *node, FILE* dot, int n)
{
    fprintf(dot, "%i [label=until];\n", n);
    int m = n;
    if (node == NULL)
        return m + 1;
    if (node->predicate != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->predicate, dot, m + 1);
    }
    if (node->statement != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->statement, dot, m = 1);
    }
    return m + 1;
}

int print_for_node(struct s_for_node *node, FILE* dot, int n)
{
    fprintf(dot, "%i [label=for];\n", n);
    int m = n;
    if (node == NULL)
        return m + 1;
    if (node->do_group != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->do_group, dot, m + 1);
    }
    return m + 1;
}
