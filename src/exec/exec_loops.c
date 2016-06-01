#include <global.h>
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
    // TODO: Implement for loop
    if (node == NULL)
        return -1;
    return -1;
}
