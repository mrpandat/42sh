#include <builtins.h>
#include <lexer.h>
#include <argument_parser.h>
#include <ctype.h>

int my_exit(struct s_simple_command_node *node)
{
    if (node->nb_elements < 2)
        return 1;
    int nb = 0;
    if (isdigit(node->elements[1]->data.word[0]))
        nb = atoi(node->elements[1]->data.word);
    else
    {
        nb = 2;
        fprintf(stderr, "exit: %s numeric argument required\n",
                node->elements[1]->data.word);
    }
    free_ast_node(g_env.root);
    lexer_destroy(g_env.lexer);
    if (strcmp(g_env.opt->file, "") != 0)
        free(g_env.opt->command);

    exit(nb);
}
