#include <global.h>
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
    // TODO: Implement case loop
    if (node == NULL)
        return -1;
    return -1;
}

int exec_case_item_node(struct s_case_item_node *node)
{
    // TODO: Implement case item
    if (node == NULL)
        return -1;
    return -1;
}
