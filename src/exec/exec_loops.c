#include <global.h>
#include <expansion.h>
#include "../includes/execute.h"

int exec_while_node(struct s_while_node *node)
{
    int ret = 0;
    while (!exec_ast_node(node->predicate))
        ret = exec_ast_node(node->statement);
    return ret;
}

int exec_until_node(struct s_until_node *node)
{
    int ret = 0;
    while (exec_ast_node(node->predicate))
        ret = exec_ast_node(node->statement);
    return ret;
}

int exec_for_node(struct s_for_node *node)
{
    if (node == NULL)
        return -1;
    int ret = 0;
    // TODO: replace words by $@ expansion if there is no word
    for (int i = 0; i < node->nb_words; i++)
    {
        set_var(node->iterator, exec_word(node->words[i]));
        ret = exec_ast_node(node->do_group);
    }
    return ret;
}
