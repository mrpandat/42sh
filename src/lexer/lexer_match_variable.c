#define _GNU_SOURCE
#include "../includes/lexer.h"


static bool match_compound_variable(struct s_lexer *lexer)
{
    /** ${ */
    char *value = NULL;

    if (0 == strncmp(lexer->current, "${", strlen("${")))
    {
        size_t len = 0;
        lexer->current += 2;
        char *copy = lexer->current;
        while (*copy && 0 != strncmp(copy, "}", strlen("}")))
        {
            len++;
            copy++;
        }

        value = strndup(lexer->current, (copy - lexer->current));
    }

    if (NULL != value && strlen(value) > 0)
    {
        lexer_add_token(lexer, TK_VARIABLE, value);
        lexer->current += (strlen(value) + 1);
        free(value);
        return true;
    }

    free(value);
    return false;
}

static bool match_simple_variable(struct s_lexer *lexer)
{
    /** $ */
    char *value = NULL;

    if (0 == strncmp(lexer->current, "$", strlen("$")))
    {
        size_t len = 0;
        lexer->current++;
        char *copy = lexer->current;
        while (*copy && 0 != is_word_letter(*copy))
        {
            len++;
            copy++;
        }

        value = strndup(lexer->current, (copy - lexer->current));
    }
    else
        return false;

    if (NULL != value && strlen(value) > 0)
    {
        lexer_add_token(lexer, TK_VARIABLE, value);
        lexer->current += (strlen(value));
    }
    else
        lexer_add_token(lexer, TK_WORD, "$");

    free(value);
    return true;
}

bool lexer_match_variable(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !strlen(lexer->current))
        return false;

    return match_compound_variable(lexer) || match_simple_variable(lexer);
}

