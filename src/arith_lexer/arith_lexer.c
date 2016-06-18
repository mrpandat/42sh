#define _GNU_SOURCE

#include "../includes/arith_lexer.h"

static bool match_separator(struct s_arlex *arlex)
{
    if (NULL == arlex || NULL == arlex->current || !strlen(arlex->current))
        return false;

    int len = 0;
    char *copy = arlex->current;

    while (!strncmp(" ", copy, strlen(" "))
           || !strncmp("\t", copy, strlen("\t")))
    {
        len++;
        copy++;
    }

    if (len > 0)
    {
        arlex->current += len;
        return true;
    }
    return false;
}

static bool match_newline_symbol(struct s_arlex *arlex)
{
    /** \n */
    if (0 == strncmp(arlex->current, "\n", strlen("\n")))
    {
        arlex_add_token(arlex, AL_NEWLINE, "\n");
        arlex->current += strlen("\n");
        return true;
    }
    return false;
}

static bool arlex_match_newline(struct s_arlex *arlex)
{
    if (NULL == arlex || NULL == arlex->current || !strlen(arlex->current))
        return false;

    return match_newline_symbol(arlex);
}

static bool arlex_match_expr(struct s_arlex *arlex)
{
    return match_separator(arlex)
           || arlex_match_newline(arlex)
           || arlex_match_symbol(arlex)
           || arlex_match_operator(arlex)
           || arlex_match_variable(arlex)
           || arlex_match_number(arlex)
           || arlex_match_undefined(arlex);
}

struct s_arlex *arlex_init(const char *expr)
{
    struct s_arlex *arlex = NULL;
    if (NULL == (arlex = malloc(sizeof (struct s_arlex))))
        return NULL;

    if (NULL == (arlex->expression = malloc(sizeof (char) * strlen(expr) + 1)))
    {
        free(arlex);
        return NULL;
    }

    strcpy(arlex->expression, expr);
    arlex->current = arlex->expression;

    arlex->altk_list = NULL;
    arlex->altk_current = NULL;

    return arlex;
}

void arlex_process(struct s_arlex *arlex)
{
    if (NULL == arlex || NULL == arlex->expression || NULL == arlex->current)
        return;

    while ('\0' != *arlex->current)
        arlex_match_expr(arlex);

    arlex_add_token(arlex, AL_EOF, "EOF");

    /** Reset current token to first element of list */
    arlex->altk_current = arlex->altk_list;
}

void arlex_destroy(struct s_arlex *arlex)
{
    if (NULL != arlex->altk_list)
    {
        struct s_arlex_token *token = arlex->altk_list;
        while (NULL != token)
        {
            struct s_arlex_token *curr = token;
            token = token->next;
            free(curr->value);
            free(curr);
        }
    }

    free(arlex->expression);
    free(arlex);
}


