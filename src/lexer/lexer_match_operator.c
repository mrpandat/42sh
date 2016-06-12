#include "../includes/lexer.h"

static bool match_if(struct s_lexer *lexer)
{
    /** if */
    if (0 == strncmp(lexer->current, "if", strlen("if")))
    {
        lexer_add_token(lexer, TK_IF, "if");
        lexer->current += strlen("if");
        return true;
    }
        /** elif */
    else if (0 == strncmp(lexer->current, "elif", strlen("elif")))
    {
        lexer_add_token(lexer, TK_ELIF, "elif");
        lexer->current += strlen("elif");
        return true;
    }
        /** else */
    else if (0 == strncmp(lexer->current, "else", strlen("else")))
    {
        lexer_add_token(lexer, TK_ELSE, "else");
        lexer->current += strlen("else");
        return true;
    }
        /** fi */
    else if (0 == strncmp(lexer->current, "fi", strlen("fi")))
    {
        lexer_add_token(lexer, TK_FI, "fi");
        lexer->current += strlen("fi");
        return true;
    }
    return false;
}

static bool match_for(struct s_lexer *lexer)
{
    /** for */
    if (0 == strncmp(lexer->current, "for", strlen("for")))
    {
        lexer_add_token(lexer, TK_FOR, "for");
        lexer->current += strlen("for");
        return true;
    }
        /** in */
    else if (0 == strncmp(lexer->current, "in", strlen("in")))
    {
        lexer_add_token(lexer, TK_IN, "in");
        lexer->current += strlen("in");
        return true;
    }
        /** done */
    else if (0 == strncmp(lexer->current, "done", strlen("done")))
    {
        lexer_add_token(lexer, TK_DONE, "done");
        lexer->current += strlen("done");
        return true;
    }
        /** do */
    else if (0 == strncmp(lexer->current, "do", strlen("do")))
    {
        lexer_add_token(lexer, TK_DO, "do");
        lexer->current += strlen("do");
        return true;
    }
    return false;
}

static bool match_case(struct s_lexer *lexer)
{
    /** case */
    if (0 == strncmp(lexer->current, "case", strlen("case")))
    {
        lexer_add_token(lexer, TK_CASE, "case");
        lexer->current += strlen("case");
        return true;
    }
        /** then */
    else if (0 == strncmp(lexer->current, "then", strlen("then")))
    {
        lexer_add_token(lexer, TK_THEN, "then");
        lexer->current += strlen("then");
        return true;
    }
        /** esac */
    else if (0 == strncmp(lexer->current, "esac", strlen("esac")))
    {
        lexer_add_token(lexer, TK_ESAC, "esac");
        lexer->current += strlen("esac");
        return true;
    }
    return false;
}

static bool match_while_until(struct s_lexer *lexer)
{
    /** while */
    if (0 == strncmp(lexer->current, "while", strlen("while")))
    {
        lexer_add_token(lexer, TK_WHILE, "while");
        lexer->current += strlen("while");
        return true;
    }
        /** until */
    else if (0 == strncmp(lexer->current, "until", strlen("until")))
    {
        lexer_add_token(lexer, TK_UNTIL, "until");
        lexer->current += strlen("until");
        return true;
    }
    return false;
}

static bool match_function(struct s_lexer *lexer)
{
    if (0 == strncmp(lexer->current, "function", strlen("function")))
    {
        lexer_add_token(lexer, TK_FUNCTION, "function");
        lexer->current += strlen("function");
        return true;
    }
    return false;
}

bool lexer_match_operator(struct s_lexer *lexer)
{
    if (NULL == lexer || NULL == lexer->current || !strlen(lexer->current))
        return false;

    return match_if(lexer) || match_for(lexer) || match_case(lexer)
           || match_while_until(lexer) || match_function(lexer);
}
