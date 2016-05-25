#include "../includes/lexer.h"

struct s_lexer *lexer_init(const char *command)
{
    struct s_lexer *lexer = NULL;
    if (NULL == (lexer = malloc(sizeof(struct s_lexer))))
        return NULL;

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

bool lexer_match_expr(struct s_lexer *lexer)
{
    return lexer_match_eof(lexer)
           || lexer_match_and_or_not(lexer)
           || lexer_match_symbol(lexer)
           || lexer_match_arith(lexer)
           || lexer_match_expansion(lexer)
           || lexer_match_operator(lexer)
           || lexer_match_word(lexer);
}

void lexer_process(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->command || NULL == lexer->current)
        return;

    while ('\0' != lexer->current)
    {
        if (!lexer_match_expr(lexer))
        {
            return;
        }
    }
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

    free(lexer);
}
