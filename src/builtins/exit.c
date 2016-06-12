#include <builtins.h>
#include <lexer.h>
#include <argument_parser.h>
#include <ctype.h>
#include <execute.h>
#include <hashtable.h>

int my_exit(struct s_simple_command_node *node)
{
    int nb = 0;
    if (node->nb_elements < 2)
        nb = 0;
    else
    {
        if (isdigit(exec_word(node->elements[1]->data.s_word)[0]))
            nb = atoi(exec_word(node->elements[1]->data.s_word));
        else
        {
            nb = 2;
            fprintf(stderr, "exit: %s numeric argument required\n",
                    exec_word(node->elements[1]->data.s_word));
        }
    }
    free_ast_node(g_env.root);
    lexer_destroy(g_env.lexer);
    if (strcmp(g_env.opt->file, "") != 0)
        free(g_env.opt->command);
    ht_destroy(g_env.aliases);
    exit(nb);
}
