#include "../includes/global.h"
#include "../includes/ast.h"

struct s_ast_node* init_ast_node(void)
{
    return malloc(sizeof (struct s_ast_node));
}
