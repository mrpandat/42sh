#define _GNU_SOURCE

#include "../includes/lexer.h"

static bool is_word_end(char *str)
{
    if (NULL == str)
        return true;

    /** (a-zA-Z0-9_) */
    if ((*str >= 'a' && *str <= 'z')
        || (*str >= 'A' && *str <= 'Z')
        || (*str >= '0' && *str <= '9')
        || '_' == *str)
        return false;

    return true;
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

    while (!is_word_end(copy))
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
