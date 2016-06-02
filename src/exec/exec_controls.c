#include <global.h>
#include <util.h>
#include "../includes/execute.h"

int exec_if_node(struct s_if_node *node)
{
    int ret = 0;
    if (!exec_ast_node(node->predicate))
        ret = exec_ast_node(node->true_statement);
    else
    {
        if (node->false_statement != NULL)
            ret = exec_ast_node(node->false_statement);
    }
    return ret;
}

int exec_case_node(struct s_case_node *node)
{
    for (int i = 0; i < node->nb_items; i++)
    {
        struct s_case_item_node *item = node->items[i];
        for (int j = 0; j < item->nb_words; j++)
        {
            if (pattern_matching(item->words[j], node->word))
                return exec_ast_node(item->statement);
        }
    }
    return 0;
}
