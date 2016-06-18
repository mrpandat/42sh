/**
** @file arith_lexer.h
** @brief Summary of all functions used to initialize an arithmetic expression
**        lexer and lex the input.
** @author Domingues T.
*/

#ifndef ARITH_LEXER_H
# define ARITH_LEXER_H

# include "../includes/global.h"

/**
** @brief Used to associate an arithmetic token value with its type (operator,
**        number, parenthesis...)
*/
enum e_arlex_type
{
    /** Unknown value */
    AL_UNDEFINED,
    /** & (bitwise operation) */
    AL_AND,
    /** | (bitwise operation) */
    AL_OR,
    /** \\n */
    AL_NEWLINE,
    /** \0 (End of input) */
    AL_EOF,
    /** + */
    AL_PLUS,
    /** - */
    AL_MINUS,
    /** ** */
    AL_POW,
    /** * */
    AL_MULT,
    /** / */
    AL_DIV,
    /** % */
    AL_MOD,
    /** ( */
    AL_LPAR,
    /** ) */
    AL_RPAR
};

/**
** @brief Represents an arithmetic expression lexer token implemented as a
**        linked list, with a type and a value.
*/
struct s_arlex_token
{
    enum e_arlex_type type;
    char *value;
    struct s_arlex_token *next;
};

/**
** @brief Represents an arithmetic expression lexer instance, containing the
**        expression to lex and a list of tokens.
*/
struct s_arlex
{
    char *expression;
    char *current;
    struct s_arlex_token *altk_list;
    struct s_arlex_token *altk_current;
};

#endif /* !ARITH_LEXER_H */
