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

/* File: arith_lexer.c */

/**
** @fn struct s_arlex *arlex_init(const char *expr)
** @brief Initialize an arithmetic expression lexer instance with a given
**        expression.
** @param The expression to lex.
** @return A structure representing the arithmetic expression lexer instance.
*/
struct s_arlex *arlex_init(const char *expr);

/**
** @fn void arlex_process(struct s_arlex *arlex)
** @brief Lex the arithmetic expression in the lexer instance, and create the
**        tokens for the parsing function.
** @param The arithmetic expression lexer instance.
*/
void arlex_process(struct s_arlex *arlex);

/**
** @fn void arlex_destroy(struct s_arlex *arlex)
** @brief Destroy an arithmetic expression lexer instance, freeing all memory
**        required for the lexer to work properly. Destroys also all the
**        tokens lexed.
** @param The arithmetic expression lexer instance.
*/
void arlex_destroy(struct s_arlex *arlex);

/* File: arlex_tokening.c */

/**
** @fn void void arlex_add_token(struct s_arlex *arlex, enum e_arlex_type type,
**          char *val)
** @brief Create a new arithmetic value token. Allocates memory for the value.
**        Type is on the stack, value is on the heap (can be shared).
** @param The arithmetic expression lexer instance.
*/
void arlex_add_token(struct s_arlex *arlex, enum e_arlex_type type, char *val);

/**
** @fn struct s_arlex_token *arlex_peek(struct s_arlex *arlex)
** @brief Returns the current token in the arlex list without consuming it.
** @param The arithmetic expression lexer instance.
** @return The current token instance, NULL if invalid arithmetic expression
**         lexer instance.
*/
struct s_arlex_token *arlex_peek(struct s_arlex *arlex);

/**
** @fn struct s_arlex_token *arlex_read(struct s_arlex *arlex)
** @brief Returns the next token in the arlex list, consuming the current.
** @param The arithmetic expression lexer instance.
** @return The next token instance, NULL if invalid arithmetic expression lexer
**         instance.
*/
struct s_arlex_token *arlex_read(struct s_arlex *arlex);

#endif /* !ARITH_LEXER_H */
