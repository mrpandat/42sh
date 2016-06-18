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
**        number, parenthesis...). Types are ranked by priority
*/
enum e_arlex_type
{
    /** + */
    AL_PLUS,
    /** - */
    AL_MINUS,
    /** ! (logical NOT) */
    AL_LG_NEG,
    /** ~ (bitwise NOT) */
    AL_BW_NEG,
    /** ** (exponentiation) */
    AL_POW,
    /** * */
    AL_MULT,
    /** / */
    AL_DIV,
    /** & (bitwise AND) */
    AL_BW_AND,
    /** ^ (bitwise XOR) */
    AL_BW_XOR,
    /** | (bitwise OR) */
    AL_BW_OR,
    /** && (logical AND) */
    AL_LG_AND,
    /** || (logical OR) */
    AL_LG_OR,
    /** ( */
    AL_LPAR,
    /** ) */
    AL_RPAR,
    /** Variable ('${VAR}', '$VAR' or 'VAR') */
    AL_VAR,
    /** Number (0-9)+ */
    AL_NUMBER,
    /** \0 (End of input) */
    AL_EOF,
    /** Unknown value */
    AL_UNDEFINED
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
