#define _GNU_SOURCE

#include <util.h>
#include "global.h"
#include "ast.h"

int print_simple_command_node(struct s_simple_command_node *node,
                              FILE* dot,
                              int n)
{
    if (node == NULL)
        return n + 1;
    int m = n;
    if (node->elements != NULL)
    {
        char *commands = strdup("");
        char *tmp;
        for (int i = 0; i < node->nb_elements; i++)
        {
            if (node->elements[i]->type == EL_WORD)
            {
                if (node->elements[i]->data.s_word->type == WD_ARITH)
                {
                    tmp = str_append(commands, "$((");
                    free(commands);
                    commands = tmp;
                    tmp = str_append(commands,
                                     node->elements[i]->data.s_word->value);
                    free(commands);
                    commands = tmp;
                    tmp = str_append(commands, "))");
                    free(commands);
                    commands = tmp;
                }
                else
                {
                    tmp = str_append(commands,
                                     node->elements[i]->data.s_word->value);
                    free(commands);
                    commands = tmp;
                }
                tmp = str_append(tmp, " ");
                free(commands);
                commands = tmp;
            }
        }
        fprintf(dot, "%i [label=\"simple command: %s\"];\n", n, commands);
        free(commands);
    }
    return m + 1;
}

int print_command_node(struct s_command_node *node, FILE* dot, int n)
{
    if (node == NULL)
        return n + 1;
    int m = n;
    fprintf(dot, "%i [label=command];\n", n);
    if (node->content != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->content, dot, m + 1);
    }
    return m + 1;
}

int print_funcdec_node(struct s_funcdec_node *node, FILE* dot, int n)
{
    if (node == NULL)
        return n + 1;
    int m = n;
    fprintf(dot, "%i [label=function];\n", n);
    if (node->shell_command != NULL)
    {
        fprintf(dot, "%i -> %i;\n", n, m + 1);
        m = print_ast_node(node->shell_command, dot, m + 1);
    }
    return m + 1;
}
