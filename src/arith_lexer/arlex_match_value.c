#define _GNU_SOURCE

#include "../includes/arith_lexer.h"

bool is_word_char(char c)
{
    if ('#' != c && '>' != c && '<' != c && '|' != c && '&' != c && '(' != c
        && ')' != c && '{' != c && '}' != c && '!' != c && ';' != c
        && '$' != c && '"' != c && '\'' != c && ' ' != c && '\n' != c
        && '\0' != c && !(c >= 48 && c <= 57))
        return true;

    return false;
}

bool is_arithmetic_letter(char c)
{
    if ('&' == c || '|' == c || '^' == c || '(' == c || ')' == c || '{' == c
        || '}' == c || '!' == c || '~' == c || '$' == c || '+' == c
        || '-' == c || '*' == c || '/' == c || ' ' == c || '\n' == c
        || '\0' == c || (c >= 48 && c <= 57) || (c >= 65 && c <= 90)
        || (c >= 97 && c <= 122) || '_' == c)
        return true;

    return false;
}

static bool match_compound_variable(struct s_arlex *arlex)
{
    /** ${ */
    if (0 == strncmp(arlex->current, "${", strlen("${")))
    {
        arlex->current += 2;
        char *begin = arlex->current;
        while ('}' != *arlex->current)
            arlex->current++;

        char *value = strndup(begin, arlex->current - begin);
        arlex_add_token(arlex, AL_VAR, value);
        arlex->current += strlen("}");

        free(value);

        return true;
    }
    return false;
}

static bool match_simple_variable(struct s_arlex *arlex)
{
    /** $ */
    if (0 == strncmp(arlex->current, "$", strlen("$")))
    {
        arlex->current++;
        char *begin = arlex->current;
        while (is_word_char(*arlex->current))
            arlex->current++;

        char *value = strndup(begin, arlex->current - begin);
        arlex_add_token(arlex, AL_VAR, value);

        free(value);

        return true;
    }
    return false;
}

static bool match_word(struct s_arlex *arlex)
{
    /** WORD */
    if (is_word_char(*arlex->current))
    {
        char *begin = arlex->current;
        while (is_word_char(*arlex->current))
            arlex->current++;

        char *value = strndup(begin, arlex->current - begin);
        arlex_add_token(arlex, AL_VAR, value);

        free(value);

        return true;
    }
    return false;
}

bool arlex_match_variable(struct s_arlex *arlex)
{
    if (NULL == arlex || NULL == arlex->current || !strlen(arlex->current))
        return false;

    return match_compound_variable(arlex) || match_simple_variable(arlex)
           || match_word(arlex);
}

bool arlex_match_number(struct s_arlex *arlex)
{
    if (NULL == arlex || NULL == arlex->current || !strlen(arlex->current))
        return false;

    char *begin = arlex->current;

    if (*arlex->current >= 48 && *arlex->current <= 57)
    {
        while (*arlex->current >= 48 && *arlex->current <= 57)
            arlex->current++;

        if (arlex->current - begin > 0)
        {
            char *value = strndup(begin, arlex->current - begin);
            arlex_add_token(arlex, AL_NUMBER, value);
            free(value);
            return true;
        }
    }

    return false;
}

bool arlex_match_undefined(struct s_arlex *arlex)
{
    if (NULL == arlex || NULL == arlex->current || !strlen(arlex->current))
        return false;

    if (!is_arithmetic_letter(*arlex->current))
    {
        char *begin = arlex->current;

        while (!is_arithmetic_letter(*arlex->current))
            arlex->current++;

        if (arlex->current - begin > 0)
        {
            char *value = strndup(begin, arlex->current++ - begin);
            arlex_add_token(arlex, AL_UNDEFINED, value);
            free(value);
            return true;
        }
    }

    return false;
}



