#define _GNU_SOURCE

#include "../includes/lexer.h"

/** \{, \|, \}, \~, \:, \;, \(, \), \", \' */
static bool is_escaped_symbol(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !strlen(lexer->current))
        return false;

    if (0 == strncmp(lexer->current, "\\\"", strlen("\\\""))
        || 0 == strncmp(lexer->current, "\\\'", strlen("\\\'"))
        || 0 == strncmp(lexer->current, "\\(", strlen("\\("))
        || 0 == strncmp(lexer->current, "\\)", strlen("\\)"))
        || 0 == strncmp(lexer->current, "\\;", strlen("\\;"))
        || 0 == strncmp(lexer->current, "\\:", strlen("\\:"))
        || 0 == strncmp(lexer->current, "\\~", strlen("\\~"))
        || 0 == strncmp(lexer->current, "\\}", strlen("\\}"))
        || 0 == strncmp(lexer->current, "\\{", strlen("\\{"))
        || 0 == strncmp(lexer->current, "\\|", strlen("\\|")))
    {
        lexer->current += 2;
        return true;
    }

    return false;
}

static bool is_word_letter(char c)
{
    if ('#' != c && '>' != c && '<' != c && '|' != c && '&' != c && '(' != c
        && ')' != c && '{' != c && '}' != c && '!' != c && ';' != c
        && '$' != c && '"' != c && '\'' != c && ' ' != c && '\n' != c
        && '\0' != c)
        return true;

    return false;
}

static bool lexer_read_identifier(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current
        || !is_word_letter(*lexer->current))
        return false;

    while (is_escaped_symbol(lexer) || is_word_letter(*lexer->current))
        lexer->current++;

    return true;
}

bool lexer_read_word(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !strlen(lexer->current))
        return false;

    char *begin = lexer->current;
    if (!lexer_read_identifier(lexer))
        return false;
    char *end = lexer->current;

    char *value = strndup(begin, end - begin);

    lexer_add_token(lexer, TK_WORD, value);

    free(value);

    return true;
}

