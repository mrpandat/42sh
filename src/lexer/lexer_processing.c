#define _GNU_SOURCE

#include "../includes/lexer.h"

static bool is_eof_symbol(char *str)
{
    if (NULL == str)
        return true;

    /** \0, ;, ;; or \n */
    if ('\0' == *str
        || 0 == strncmp(str, ";", strlen(";"))
        || 0 == strncmp(str, ";;", strlen(";;"))
        || 0 == strncmp(str, "\n", strlen("\n")))
        return true;

    return false;
}

static bool match_eof_symbol(struct s_lexer *lexer)
{
    /** ; */
    if (0 == strncmp(lexer->current, ";", strlen(";")))
    {
        lexer_add_token(lexer, TK_SEMI, ";");
        lexer->current += strlen(";");
        return true;
    }
    /** ;; */
    else if (0 == strncmp(lexer->current, ";;", strlen(";;")))
    {
        lexer_add_token(lexer, TK_DSEMI, ";;");
        lexer->current += strlen(";;");
        return true;
    }
    /** \n */
    else if (0 == strncmp(lexer->current, "\n", strlen("\n")))
    {
        lexer_add_token(lexer, TK_NEWLINE, "\n");
        lexer->current += strlen("\n");
        return true;
    }
    return false;
}

bool lexer_match_eof(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !strlen(lexer->current))
        return false;

    return match_eof_symbol(lexer);
}

bool lexer_match_arith(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !strlen(lexer->current))
        return false;

    /** $(( */
    if (0 == strncmp(lexer->current, "$((", strlen("$((")))
    {
        lexer_add_token(lexer, TK_LARITH, "$((");
        lexer->current += strlen("$((");
        return true;
    }
    /** )) */
    else if (0 == strncmp(lexer->current, "))", strlen("))")))
    {
        lexer_add_token(lexer, TK_RARITH, "))");
        lexer->current += strlen("))");
        return true;
    }
    return false;
}

bool lexer_match_expansion(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !strlen(lexer->current))
        return false;

    /** $( */
    if (0 == strncmp(lexer->current, "$(", strlen("$(")))
    {
        lexer_add_token(lexer, TK_LEXPR, "$(");
        lexer->current += strlen("$(");
        return true;
    }
    return false;
}

bool lexer_match_word(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !strlen(lexer->current))
        return false;

    size_t len = 0;
    char *val = NULL;
    char *copy = lexer->current;

    while (!is_eof_symbol(copy))
    {
        len++;
        copy++;
    }

    val = strndup(lexer->current, len);

    if (NULL != val && strlen(val) > 0)
    {
        lexer_add_token(lexer, TK_WORD, val);
        lexer->current += strlen(val);
        return true;
    }
    return false;
}
