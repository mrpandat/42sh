#include "global.h"
#include "ast.h"

struct s_ast_node *init_ast_node(void)
{
    return calloc(1, sizeof (struct s_ast_node));
}

struct s_redirection_node *init_redirection_node(void)
{
    struct s_redirection_node *node =
            malloc(sizeof (struct s_redirection_node));
    node->io_number = NULL;
    node->type = NULL;
    node->word = NULL;
    return node;
}
