#define _GNU_SOURCE

#include "../includes/lexer.h"

static bool lexer_peek_char(struct s_lexer *lexer, char c)
{
    if (NULL == lexer || NULL == lexer->current)
        return false;

    if (*lexer->current == c)
        return true;

    return false;
}

static bool lexer_read_range(struct s_lexer *lexer, char begin, char end)
{
    if (NULL == lexer || NULL == lexer->current)
        return false;

    if (*lexer->current >= begin && *lexer->current <= end)
    {
        lexer->current++;
        return true;
    }

    return false;
}

static bool lexer_read_identifier(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current
        || (!lexer_read_range(lexer, 'a', 'z')
            && !lexer_read_range(lexer, 'A', 'Z')
            && !lexer_peek_char(lexer, '_')
            && !lexer_peek_char(lexer, '/')
            && !lexer_peek_char(lexer, '.')))
        return false;

    while ((*lexer->current >= 'a' && *lexer->current <= 'z')
           || (*lexer->current >= 'A' && *lexer->current <= 'Z')
           || (*lexer->current >= '0' && *lexer->current <= '9')
           || lexer_peek_char(lexer, '_')
           || lexer_peek_char(lexer, '/')
           || lexer_peek_char(lexer, '.'))
        lexer->current++;

    return true;
}

bool lexer_read_word(struct s_lexer *lexer)
{
    char *begin = lexer->current;
    if (!lexer_read_identifier(lexer))
        return false;
    char *end = lexer->current;

    char *value = strndup(begin, end - begin);

    lexer_add_token(lexer, TK_WORD, value);

    return true;
}

