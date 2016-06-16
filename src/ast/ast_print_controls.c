#define _GNU_SOURCE

#include "global.h"
#include "ast.h"
#include <util.h>

int print_if_node(struct s_if_node *node, FILE* dot, int n)
{
    fprintf(dot, "%i [label=if];\n", n);
    if (node == NULL)
        return n + 1;
    int m = n;
    if (node->predicate != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->predicate, dot, m + 1);
    }
    if (node->true_statement != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->true_statement, dot, m + 1);
    }
    if (node->false_statement != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->false_statement, dot, m + 1);
    }
    return m + 1;
}

int print_case_node(struct s_case_node *node, FILE* dot, int n)
{
    fprintf(dot, "%i [label=case];\n", n);
    if (node == NULL)
        return n + 1;
    int m = n;
    if (node->items != NULL)
    {
        for (int i = 0; i < node->nb_items; i++)
        {
            fprintf(dot, "%i -> %i;\n", n, m + 1);
            m = print_case_item_node(node->items[i], dot, m + 1);
        }
    }
    return m + 1;
}

int print_case_item_node(struct s_case_item_node *node, FILE* dot, int n)
{
    fprintf(dot, "%i [label=case];\n", n);
    if (node == NULL)
        return n + 1;
    int m = n;
    if (node->words != NULL)
    {
        char *items = strdup("");
        char *tmp;
        for (int i = 0; i < node->nb_words; i++)
        {
            tmp = str_append(items, node->words[i]);
            free(items);
            items = tmp;
            tmp = str_append(tmp, " ");
            free(items);
            items = tmp;
        }
        fprintf(dot, "%i [label=\"case item: %s\"];\n", n, items);
        free(items);
    }
    if (node->statement != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->statement, dot, m + 1);
    }
    return m + 1;
}
