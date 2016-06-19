#define _GNU_SOURCE

#include "../includes/ast.h"
#include "../includes/parser.h"
#include "../includes/util.h"
#include "../includes/global.h"

bool read_prefix(struct s_element_node *element, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_ASSIGNEMENT)
    {
        element->type = EL_WORD;
        element->data.s_word = init_word(is_word(lexer_peek(l)), lexer_peek(l)->value);
        lexer_read(l);
        return true;
    }
    else
    {
        element->type = EL_REDIRECTION;
        element->data.s_redirection_node = init_redirection_node();
        if (read_redirection(element->data.s_redirection_node, l))
            return true;
        else
        {
            element->type = EL_NONE;
            free_redirection_node(element->data.s_redirection_node);
            return false;
        }
    }
}

int read_element(struct s_element_node *element, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_WORD || lexer_peek(l)->type == TK_ESC_WORD
        || lexer_peek(l)->type == TK_VARIABLE)
    {
        element->type = EL_WORD;
        element->data.s_word = init_word(is_word(lexer_peek(l)),
                                         lexer_peek(l)->value);
        lexer_read(l);
        return 1;
    }
    else if (lexer_peek(l)->type == TK_LARITH)
        return read_arithmetic_expansion(element, l);
    else if (lexer_peek(l)->type == TK_LEXPR)
        return read_subshell(element, l);
    else
    {
        element->type = EL_REDIRECTION;
        element->data.s_redirection_node = init_redirection_node();
        if (read_redirection(element->data.s_redirection_node, l))
            return 1;
        else
        {
            element->type = EL_NONE;
            free_redirection_node(element->data.s_redirection_node);
            return 0;
        }
    }
}

static int pars_count(struct s_lexer *l)
{
    enum e_token_type type = lexer_peek(l)->type;
    if (type == TK_LPAR)
        return 1;
    else if (type == TK_RPAR)
        return -1;
    else if (type == TK_RARITH)
        return -2;
    else
        return 0;
}

int read_arithmetic_expansion(struct s_element_node *element,
                               struct s_lexer *l)
{
    if (lexer_peek(l)->type != TK_LARITH)
        return 0;
    int pars = 2;
    lexer_read(l);
    char *expression = strdup("");
    char *temp;
    enum e_token_type type = lexer_peek(l)->type;
    while (type == TK_WORD || type == TK_LPAR || type == TK_RPAR
           || type == TK_RARITH || type == TK_IONUMBER || type == TK_BANG)
    {
        temp = str_append(expression, lexer_peek(l)->value);
        free(expression);
        expression = temp;
        pars += pars_count(l);
        lexer_read(l);
        if (pars <= 0)
            break;
        type = lexer_peek(l)->type;
    }
    element->type = EL_WORD;
    element->data.s_word = init_word(WD_ARITH, expression);
    if (pars != 0 || strlen(expression) <= 2)
        return -1;
    expression[strlen(expression) - 2] = '\0';
    return 1;
}

int read_subshell(struct s_element_node *element,
                  struct s_lexer *l)
{
    if (lexer_peek(l)->type != TK_LEXPR)
        return 0;
    int pars = 1;
    lexer_read(l);
    char *expression = strdup("");
    enum e_token_type type = lexer_peek(l)->type;
    while (type != TK_EOF)
    {
        expression = str_append_free(expression, lexer_peek(l)->value);
        pars += pars_count(l);
        lexer_read(l);
        if (pars <= 0)
            break;
        expression = str_append_free(expression, " ");
        type = lexer_peek(l)->type;
    }
    element->type = EL_WORD;
    element->data.s_word = init_word(WD_SUBSHELL, expression);
    if (pars != 0 || strlen(expression) <= 2)
        return -1;
    expression[strlen(expression) - 2] = '\0';
    return 1;
}

int read_var_expansion(struct s_element_node *element,
                       struct s_lexer *l)
{
    if (lexer_peek(l)->type != TK_LEXPR)
        return 0;
    int pars = 1;
    lexer_read(l);
    char *expression = strdup("");
    enum e_token_type type = lexer_peek(l)->type;
    while (type != TK_EOF)
    {
        expression = str_append_free(expression, lexer_peek(l)->value);
        pars += pars_count(l);
        lexer_read(l);
        if (pars <= 0)
            break;
        expression = str_append_free(expression, " ");
        type = lexer_peek(l)->type;
    }
    element->type = EL_WORD;
    element->data.s_word = init_word(WD_SUBSHELL, expression);
    if (pars != 0 || strlen(expression) <= 2)
        return -1;
    expression[strlen(expression) - 2] = '\0';
    return 1;
}
