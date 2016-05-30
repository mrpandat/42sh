#include "global.h"
#include "ast.h"

struct s_element_node *init_element_node(void)
{
    struct s_element_node *node = malloc(sizeof (struct s_element_node));
    node->type = EL_NONE;
    return node;
}

