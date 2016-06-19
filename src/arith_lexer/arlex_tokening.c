#define _GNU_SOURCE

#include "../includes/arith_lexer.h"

void arlex_add_token(struct s_arlex *arlex, enum e_arlex_type type, char *val)
{
    if (NULL == arlex || NULL == val)
        return;

    struct s_arlex_token *token = NULL;

    if (NULL == (token = malloc(sizeof (struct s_arlex_token))))
        return;

    /** Create new token */
    token->type = type;
    token->value = strdup(val);
    token->next = NULL;

    if (NULL == arlex->altk_list)
    {
        arlex->altk_list = token;
        arlex->altk_current = token;
    }
    else
    {
        arlex->altk_current->next = token;
        arlex->altk_current = arlex->altk_current->next;
    }
}

struct s_arlex_token *arlex_peek(struct s_arlex *arlex)
{
    if (NULL == arlex || NULL == arlex->altk_current)
        return NULL;

    return arlex->altk_current;
}

struct s_arlex_token *arlex_read(struct s_arlex *arlex)
{
    if (NULL == arlex || NULL == arlex->altk_current)
        return NULL;

    arlex->altk_current = arlex->altk_current->next;

    return arlex->altk_current;
}

