#include <builtins.h>
#include <lexer.h>
#include <argument_parser.h>

int my_exit(struct s_simple_command_node *node)
{
    if (node->nb_elements < 2)
        return 1;
    int nb = atoi(node->elements[1]->data.word);
    free_ast_node(g_env.root);
    lexer_destroy(g_env.lexer);
    if (strcmp(g_env.opt->file, "") != 0)
        free(g_env.opt->command);
    exit(nb);
}
