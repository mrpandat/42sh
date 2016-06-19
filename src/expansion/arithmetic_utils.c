#define _GNU_SOURCE

#include <arith_lexer.h>
#include "../includes/global.h"
#include "../includes/expansion.h"
#include "../includes/util.h"

char *arithmetic_expansion(char *expression)
{
    struct s_arlex *lexer = arlex_init(expression);
    arlex_process(lexer);
    if (lexer == NULL)
        return NULL;
    struct s_art_node *root = shunting_yard(lexer); //read_j(s);
    if (root != NULL)
    {
        int res = execute_art_node(root);
        free_art_node(root);
        arlex_destroy(lexer);
        return my_itoa(res);
    }
    else
    {
        arlex_destroy(lexer);
        return "";
    }
}
