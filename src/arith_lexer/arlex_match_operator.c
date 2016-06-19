#include "../includes/arith_lexer.h"

static bool match_exponentiation(struct s_arlex *arlex)
{
    /** ** (exponentiation) */
    if (0 == strncmp(arlex->current, "**", strlen("**")))
    {
        arlex_add_token(arlex, AL_POW, "**");
        arlex->current += strlen("**");
        return true;
    }
    return false;
}

static bool match_operation(struct s_arlex *arlex)
{
    /** + */
    if (0 == strncmp(arlex->current, "+", strlen("+")))
    {
        arlex_add_token(arlex, AL_PLUS, "+");
        arlex->current += strlen("+");
        return true;
    }
    /** - */
    else if (0 == strncmp(arlex->current, "-", strlen("-")))
    {
        arlex_add_token(arlex, AL_MINUS, "-");
        arlex->current += strlen("-");
        return true;
    }
    /** * */
    else if (0 == strncmp(arlex->current, "*", strlen("*")))
    {
        arlex_add_token(arlex, AL_MULT, "*");
        arlex->current += strlen("*");
        return true;
    }
    /** / */
    else if (0 == strncmp(arlex->current, "/", strlen("/")))
    {
        arlex_add_token(arlex, AL_DIV, "/");
        arlex->current += strlen("/");
        return true;
    }
    return false;
}

static bool match_logical(struct s_arlex *arlex)
{
    /** && */
    if (0 == strncmp(arlex->current, "&&", strlen("&&")))
    {
        arlex_add_token(arlex, AL_LG_AND, "&&");
        arlex->current += strlen("&&");
        return true;
    }
    /** || */
    else if (0 == strncmp(arlex->current, "||", strlen("||")))
    {
        arlex_add_token(arlex, AL_LG_OR, "||");
        arlex->current += strlen("||");
        return true;
    }
    /** ! (logical NOT) */
    else if (0 == strncmp(arlex->current, "!", strlen("!")))
    {
        arlex_add_token(arlex, AL_LG_NEG, "!");
        arlex->current += strlen("!");
        return true;
    }
    return false;
}

static bool match_bitwise(struct s_arlex *arlex)
{
    /** & */
    if (0 == strncmp(arlex->current, "&", strlen("&")))
    {
        arlex_add_token(arlex, AL_BW_AND, "&");
        arlex->current += strlen("&");
        return true;
    }
    /** ^ */
    else if (0 == strncmp(arlex->current, "^", strlen("^")))
    {
        arlex_add_token(arlex, AL_BW_XOR, "^");
        arlex->current += strlen("^");
        return true;
    }
    /** | */
    else if (0 == strncmp(arlex->current, "|", strlen("|")))
    {
        arlex_add_token(arlex, AL_BW_OR, "|");
        arlex->current += strlen("|");
        return true;
    }
    /** ~ */
    else if (0 == strncmp(arlex->current, "~", strlen("~")))
    {
        arlex_add_token(arlex, AL_BW_NEG, "~");
        arlex->current += strlen("~");
        return true;
    }
    return false;
}

static bool match_parenthesis(struct s_arlex *arlex)
{
    /** ( */
    if (0 == strncmp(arlex->current, "(", strlen("(")))
    {
        arlex_add_token(arlex, AL_LPAR, "(");
        arlex->current += strlen("(");
        return true;
    }
    /** ) */
    else if (0 == strncmp(arlex->current, ")", strlen(")")))
    {
        arlex_add_token(arlex, AL_RPAR, ")");
        arlex->current += strlen(")");
        return true;
    }
    return false;
}

bool arlex_match_operator(struct s_arlex *arlex)
{
    if (NULL == arlex || NULL == arlex->current || !strlen(arlex->current))
        return false;

    return match_exponentiation(arlex) || match_operation(arlex)
           || match_logical(arlex) || match_bitwise(arlex)
           || match_parenthesis(arlex);
}


