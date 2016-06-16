#define _GNU_SOURCE

#include "../includes/lexer.h"

static bool match_separator(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !strlen(lexer->current))
        return false;

    int len = 0;
    char *copy = lexer->current;

    while (!strncmp(" ", copy, strlen(" "))
           || !strncmp("\t", copy, strlen("\t")))
    {
        len++;
        copy++;
    }

    if (len > 0)
    {
        lexer->current += len;
        return true;
    }
    return false;
}

struct s_lexer *lexer_init(const char *command)
{
    struct s_lexer *lexer = NULL;
    if (NULL == (lexer = malloc(sizeof (struct s_lexer))))
        return NULL;

    if (NULL == (lexer->command = malloc(sizeof (char) * strlen(command) + 1)))
    {
        free(lexer);
        return NULL;
    }

    strcpy(lexer->command, command);
    lexer->current = lexer->command;

    lexer->tk_list = NULL;
    lexer->tk_current = NULL;

    return lexer;
}

int lexer_current_position(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->tk_list || NULL == lexer->tk_current)
        return -1;

    int pos = 0;
    struct s_lexer_token *list = lexer->tk_list;

    while (NULL != list && list != lexer->tk_current)
    {
        pos++;
        list = list->next;
    }

    if (NULL == list)
        return -1;

    return pos;
}

static bool lexer_match_expr(struct s_lexer *lexer)
{
    return match_separator(lexer)
           || lexer_match_eof(lexer)
           || lexer_match_and_or_not(lexer)
           || lexer_match_dquote(lexer)
           || lexer_match_quote(lexer)
           || lexer_match_arith(lexer)
           || lexer_match_symbol(lexer)
           || lexer_match_expansion(lexer)
           || lexer_match_variable(lexer)
           || lexer_match_operator(lexer)
           || lexer_read_word(lexer);
}

int lexer_token_list_size(struct s_lexer *lexer)
{
    if (NULL == lexer)
        return -1;

    if (NULL == lexer->tk_list)
        return 0;

    struct s_lexer_token *list = lexer->tk_list;
    int size = 0;

    while (NULL != list)
    {
        size++;
        list = list->next;
    }

    return size;
}

void lexer_process(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->command || NULL == lexer->current)
        return;

    while ('\0' != *lexer->current)
    {
        if (!lexer_match_expr(lexer))
            return;
    }

    lexer_add_token(lexer, TK_EOF, "EOF");

    /** Reset current token to first element of list */
    lexer->tk_current = lexer->tk_list;
}

void lexer_destroy(struct s_lexer *lexer)
{
    if (NULL != lexer->tk_list)
    {
        struct s_lexer_token *token = lexer->tk_list;
        while (NULL != token)
        {
            struct s_lexer_token *curr = token;
            token = token->next;
            free(curr->value);
            free(curr);
        }
    }

    free(lexer->command);
    free(lexer);
}
