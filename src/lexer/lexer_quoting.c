#define _GNU_SOURCE

#include "../includes/lexer.h"

bool match_escaped_quote(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !*lexer->current)
        return false;

    if (0 == strncmp(lexer->current, "\\\"", strlen("\\\"")))
        return true;
    else if (0 == strncmp(lexer->current, "\\'", strlen("\\'")))
        return true;

    return false;
}

bool match_escaped_symbol(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !*lexer->current)
        return false;

    if (0 == strncmp(lexer->current, "\\$", strlen("\\$")))
        return true;
    else if (0 == strncmp(lexer->current, "\\`", strlen("\\`")))
        return true;
    else if (0 == strncmp(lexer->current, "\\\\", strlen("\\\\")))
        return true;
    else if (0 == strncmp(lexer->current, "\\\n", strlen("\\\n")))
        return true;

    return false;
}

bool lexer_match_quote(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !*lexer->current)
        return false;

    size_t len = 0;
    char *val = NULL;
    char *copy = NULL;

    if (0 == strncmp(lexer->current, "'", strlen("'")))
    {
        lexer->current++;
        copy = lexer->current;

        while (*copy && 0 != strncmp(copy, "'", strlen("'")))
        {
            len++;
            copy++;
        }
    }

    val = strndup(lexer->current, len);

    if (NULL != val && strlen(val) > 0)
    {
        lexer_add_token(lexer, TK_ESC_WORD, val);
        lexer->current += (strlen(val) + 1);
        return true;
    }
    free(val);
    return false;
}

bool lexer_match_dquote(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !*lexer->current)
        return false;

    char *val = NULL;

    if (0 == strncmp(lexer->current, "\"", strlen("\"")))
    {
        lexer->current++;
        char *copy = lexer->current;

        while (*copy && 0 != strncmp(copy, "\"", strlen("\"")))
        {
            if (0 == strncmp(lexer->current, "\\\"", strlen("\\\"")))
            {
                copy += strlen("\\\"");
                continue;
            }
            copy++;
        }

        val = strndup(lexer->current, (copy - lexer->current));
    }

    if (NULL != val && strlen(val) > 0)
    {
        lexer_add_token(lexer, TK_WORD, val);
        lexer->current += (strlen(val) + 1);
        return true;
    }
    return false;
}
