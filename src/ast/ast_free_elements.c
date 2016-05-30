#include "global.h"
#include "ast.h"

void free_element_node(struct s_element_node *node)
{
    if (node == NULL)
        return;
    else if (node->type == EL_REDIRECTION)
        free_redirection_node(node->data.s_redirection_node);
    free(node);
}
