#include "../includes/lexer.h"

void lexer_add_token(struct s_lexer *lexer, enum e_token_type type, char *val)
{
    if (NULL == lexer || NULL == val)
        return;

    struct s_lexer_token *token = NULL;

    if (NULL == (token = malloc(sizeof (struct s_lexer_token))))
        return;

    /** Create new token */
    token->type = type;
    token->value = val;
    token->next = NULL;

    if (NULL == lexer->tk_list)
    {
        lexer->tk_list = token;
        lexer->tk_current = token;
    }
    else
    {
        lexer->tk_current->next = token;
        lexer->tk_current = lexer->tk_current->next;
    }
}

struct s_lexer_token *lexer_peek(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->tk_current)
        return NULL;

    return lexer->tk_current;
}

struct s_lexer_token *lexer_read(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->tk_current)
        return NULL;

    lexer->tk_current = lexer->tk_current->next;

    return lexer->tk_current;
}

struct s_lexer_token *lexer_next_token(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->tk_current
        || NULL == lexer->tk_current->next)
        return NULL;

    return lexer->tk_current->next;
}

void lexer_jump_token(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->tk_current)
        return;

    lexer->tk_current = lexer->tk_current->next;
}
