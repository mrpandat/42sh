#include "../includes/lexer.h"

static bool match_comment(struct s_lexer *lexer)
{
    /** # */
    if (0 == strncmp(lexer->current, "#", strlen("#")))
    {
        // Process as a comment to the next newline or EOF
        while (*lexer->current && '\n' != *lexer->current)
            lexer->current++;
        return true;
    }
    return false;
}

static bool match_redir(struct s_lexer *lexer)
{
    /** >& */
    if (0 == strncmp(lexer->current, ">&", strlen(">&")))
    {
        lexer_add_token(lexer, TK_GREATAND, ">&");
        lexer->current += strlen(">&");
        return true;
    }
    /** <& */
    else if (0 == strncmp(lexer->current, "<&", strlen("<&")))
    {
        lexer_add_token(lexer, TK_LESSAND, "<&");
        lexer->current += strlen("<&");
        return true;
    }
    /** >| */
    else if (0 == strncmp(lexer->current, ">|", strlen(">|")))
    {
        lexer_add_token(lexer, TK_CLOBBER, ">|");
        lexer->current += strlen(">|");
        return true;
    }
    /** <> */
    else if (0 == strncmp(lexer->current, "<>", strlen("<>")))
    {
        lexer_add_token(lexer, TK_LESSGREAT, "<>");
        lexer->current += strlen("<>");
        return true;
    }
    return false;
}

static bool match_io(struct s_lexer *lexer)
{
    /** < */
    if (0 == strncmp(lexer->current, "<", strlen("<")))
    {
        lexer_add_token(lexer, TK_LESS, "<");
        lexer->current += strlen("<");
        return true;
    }
    /** > */
    else if (0 == strncmp(lexer->current, ">", strlen(">")))
    {
        lexer_add_token(lexer, TK_GREAT, ">");
        lexer->current += strlen(">");
        return true;
    }
    return false;
}

static bool match_ionumber(struct s_lexer *lexer)
{
    /** 0 */
    if (0 == strncmp(lexer->current, "0", strlen("0")))
    {
        lexer_add_token(lexer, TK_IONUMBER, "0");
        lexer->current += strlen("0");
        return true;
    }
    /** 1 */
    else if (0 == strncmp(lexer->current, "1", strlen("1")))
    {
        lexer_add_token(lexer, TK_IONUMBER, "1");
        lexer->current += strlen("1");
        return true;
    }
    /** 2 */
    else if (0 == strncmp(lexer->current, "2", strlen("2")))
    {
        lexer_add_token(lexer, TK_IONUMBER, "2");
        lexer->current += strlen("2");
        return true;
    }
    return false;
}

static bool match_iohere(struct s_lexer *lexer)
{
    /** <<- */
    if (0 == strncmp(lexer->current, "<<-", strlen("<<-")))
    {
        lexer_add_token(lexer, TK_DLESSDASH, "<<-");
        lexer->current += strlen("<<-");
        return true;
    }
    /** << */
    else if (0 == strncmp(lexer->current, "<<", strlen("<<")))
    {
        lexer_add_token(lexer, TK_DLESS, "<<");
        lexer->current += strlen("<<");
        return true;
    }
    /** >> */
    else if (0 == strncmp(lexer->current, ">>", strlen(">>")))
    {
        lexer_add_token(lexer, TK_DGREAT, ">>");
        lexer->current += strlen(">>");
        return true;
    }
    return false;
}

static bool match_bracket(struct s_lexer *lexer)
{
    /** ( */
    if (0 == strncmp(lexer->current, "(", strlen("(")))
    {
        lexer_add_token(lexer, TK_LPAR, "(");
        lexer->current += strlen("(");
        return true;
    }
    /** ) */
    else if (0 == strncmp(lexer->current, ")", strlen(")")))
    {
        lexer_add_token(lexer, TK_RPAR, ")");
        lexer->current += strlen(")");
        return true;
    }
    /** { */
    else if (0 == strncmp(lexer->current, "{", strlen("{")))
    {
        lexer_add_token(lexer, TK_LBRACE, "{");
        lexer->current += strlen("{");
        return true;
    }
    /** } */
    else if (0 == strncmp(lexer->current, "}", strlen("}")))
    {
        lexer_add_token(lexer, TK_RBRACE, "}");
        lexer->current += strlen("}");
        return true;
    }
    return false;
}

static bool match_binary_op(struct s_lexer *lexer)
{
    /** & */
    if (0 == strncmp(lexer->current, "&", strlen("&")))
    {
        lexer_add_token(lexer, TK_AND, "&");
        lexer->current += strlen("&");
        return true;
    }
    /** | */
    else if (0 == strncmp(lexer->current, "|", strlen("|")))
    {
        lexer_add_token(lexer, TK_OR, "|");
        lexer->current += strlen("|");
        return true;
    }
    return false;
}

bool lexer_match_and_or_not(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !strlen(lexer->current))
        return false;

    /** && */
    if (0 == strncmp(lexer->current, "&&", strlen("&&")))
    {
        lexer_add_token(lexer, TK_AND_IF, "&&");
        lexer->current += strlen("&&");
        return true;
    }
    /** || */
    else if (0 == strncmp(lexer->current, "||", strlen("||")))
    {
        lexer_add_token(lexer, TK_OR_IF, "||");
        lexer->current += strlen("||");
        return true;
    }
    /** ! */
    else if (0 == strncmp(lexer->current, "!", strlen("!")))
    {
        lexer_add_token(lexer, TK_BANG, "!");
        lexer->current += strlen("!");
        return true;
    }
    return false;
}

bool lexer_match_symbol(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !strlen(lexer->current))
        return false;

    return match_comment(lexer) || match_redir(lexer) || match_ionumber(lexer)
           || match_iohere(lexer) || match_io(lexer) || match_bracket(lexer)
           || match_binary_op(lexer);
}

