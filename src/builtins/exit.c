#include <builtins.h>
#include <lexer.h>

void my_exit(int n)
{
    free_ast_node(g_ast_utils.root);
    lexer_destroy(g_ast_utils.lexer);
    exit(n);
}
