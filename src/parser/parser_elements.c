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

bool read_element(struct s_element_node *element, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_WORD || lexer_peek(l)->type == TK_ESC_WORD)
    {
        element->type = EL_WORD;
        element->data.s_word = init_word(is_word(lexer_peek(l)), lexer_peek(l)->value);
        lexer_read(l);
        return true;
    }
    else if (lexer_peek(l)->type == TK_LARITH)
        return read_arithmetic_expansion(element, l);
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

bool read_arithmetic_expansion(struct s_element_node *element,
                               struct s_lexer *l)
{
    if (lexer_peek(l)->type != TK_LARITH)
        return false;
    int pars = 2;
    lexer_read(l);
    element->type = EL_WORD;
    char *expression = strdup("");
    char *temp;
    element->data.s_word = init_word(WD_ARITH, NULL);
    enum e_token_type type = lexer_peek(l)->type;
    while (type == TK_WORD || type == TK_LPAR || type == TK_RPAR
           || type == TK_RARITH || type == TK_IONUMBER)
    {
        temp = str_append(expression, lexer_peek(l)->value);
        free(expression);
        expression = temp;
        lexer_read(l);
        if (type == TK_LPAR)
            pars++;
        if (type == TK_RPAR)
            pars--;
        if (type == TK_RARITH)
            pars -= 2;
        if (type == TK_RARITH && pars <= 0)
            break;
        type = lexer_peek(l)->type;
    }
    if (pars != 0 || strlen(expression) <= 2)
        return false;
    expression[strlen(expression) - 2] = '\0';
    element->data.s_word->value = expression;
    return true;
}
