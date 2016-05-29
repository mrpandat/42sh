/**
** @file lexer.h
** @brief Summary of all functions used to initialize a lexer and lex the input.
** @author Domingues T.
*/

#ifndef LEXER_LEXER_H
# define LEXER_LEXER_H

# include "../includes/global.h"

/**
** @brief Used to associate a token value with it's type (command, function...)
*/
enum e_token_type
{
    /** Type to be defined */
    TK_UNDEFINED,
    /** & (bitwise operation) */
    TK_AND,
    /** | (bitwise operation) */
    TK_OR,
    /** && */
    TK_AND_IF,
    /** || */
    TK_OR_IF,
    /** \\n */
    TK_NEWLINE,
    /** \0 */
    TK_EOF,
    /** ; */
    TK_SEMI,
    /** ;; */
    TK_DSEMI,
    /** ! */
    TK_BANG,
    /** $( */
    TK_LEXPR,
    /** ( */
    TK_LPAR,
    /** ) */
    TK_RPAR,
    /** { */
    TK_LBRACE,
    /** } */
    TK_RBRACE,
    /** > */
    TK_GREAT,
    /** >> */
    TK_DGREAT,
    /** < */
    TK_LESS,
    /** << */
    TK_DLESS,
    /** <<- */
    TK_DLESSDASH,
    /** >& */
    TK_GREATAND,
    /** <& */
    TK_LESSAND,
    /** >| */
    TK_CLOBBER,
    /** <> */
    TK_LESSGREAT,
    /** $(( */
    TK_LARITH,
    /** )) */
    TK_RARITH,
    /** Word without any expansion done into */
    TK_ESC_WORD,
    /** Word (a-zA-Z_)[(a-zA-Z0-9_)]* */
    TK_WORD,
    /** "if" */
    TK_IF,
    /** "then" */
    TK_THEN,
    /** "else" */
    TK_ELSE,
    /** "elif" */
    TK_ELIF,
    /** "fi" */
    TK_FI,
    /** "do" */
    TK_DO,
    /** "done" */
    TK_DONE,
    /** "case" */
    TK_CASE,
    /** "esac" */
    TK_ESAC,
    /** "while" */
    TK_WHILE,
    /** "until" */
    TK_UNTIL,
    /** "for" */
    TK_FOR,
    /** "in" */
    TK_IN,
    /** "function" */
    TK_FUNCTION,
    /** 0, 1 or 2 */
    TK_IONUMBER,
    /** << with */
    TK_HEREDOC,
    /** set */
    TK_ASSIGNEMENT
};

/**
** @brief Represents a Lexer token implemented as a linked list, with a type
**        and a value.
*/
struct s_lexer_token
{
    enum e_token_type type;
    char *value;
    struct s_lexer_token *next;
};

/**
** @brief Represents a Lexer instance, containing the command and a list of
**        tokens.
*/
struct s_lexer
{
    char *command;
    char *current;
    struct s_lexer_token *tk_list;
    struct s_lexer_token *tk_current;
};

/* File: lexer.c */

/**
** @fn struct s_lexer *lexer_init(const char *command)
** @brief Initialize a lexer instance with a given command.
** @param The command to lex.
** @return A structure representing the lexer instance.
*/
struct s_lexer *lexer_init(const char *command);

/**
** @fn int lexer_current_position(struct s_lexer *lexer)
** @brief Get the position of a token in the token list, from 0 to n - 1.
** @param The lexer instance.
** @return The current position, or -1 if invalid lexer.
*/
int lexer_current_position(struct s_lexer *lexer);

/**
** @fn void lexer_process(struct s_lexer *lexer)
** @brief Lex the command in the lexer instance, and create the tokens for the
**        parsing function.
** @param The lexer instance.
*/
void lexer_process(struct s_lexer *lexer);

/**
** @fn void lexer_process(struct s_lexer *lexer)
** @brief Lex the command in the lexer instance, and create the tokens for the
**        parsing function.
** @param The lexer instance.
 * @return true if command is lexically valid, false otherwise.
*/
bool lexer_match_expr(struct s_lexer *lexer);

/**
** @fn void lexer_destroy(struct s_lexer *lexer)
** @brief Destroy a lexer instance, freeing all memory required for the lexer to
**        work properly. Destroys also all the tokens lexed.
** @param The lexer instance.
*/
void lexer_destroy(struct s_lexer *lexer);

/* File: lexer_tokening.c */

/**
** @fn void lexer_add_token(struct s_lexer *lexer, enum e_token_type type,
**          char *val)
** @brief Create a new token. Allocates memory for the value. Type is on the
**        stack, value is on the heap (can be shared).
** @param The lexer instance.
*/
void lexer_add_token(struct s_lexer *lexer, enum e_token_type type, char *val);

/**
** @fn struct s_lexer_token *lexer_peek(struct s_lexer *lexer)
** @brief Returns the current token in the list without consuming it.
** @param The lexer instance.
** @return The current token instance, NULL if invalid lexer instance.
*/
struct s_lexer_token *lexer_peek(struct s_lexer *lexer);

/**
** @fn struct s_lexer_token *lexer_read(struct s_lexer *lexer)
** @brief Returns the next token in the list, consuming the current.
** @param The lexer instance.
** @return The next token instance, NULL if invalid lexer instance.
*/
struct s_lexer_token *lexer_read(struct s_lexer *lexer);

/**
** @fn struct s_lexer_token *lexer_next_token(struct s_lexer *lexer)
** @brief Returns the next token in the list without consuming the current.
** @param The lexer instance.
** @return The next token instance, NULL if invalid lexer instance.
*/
struct s_lexer_token *lexer_next_token(struct s_lexer *lexer);

/**
** @fn struct s_lexer_token *lexer_jump_token(struct s_lexer *lexer)
** @brief Consume the current token without returning it.
** @param The lexer instance.
*/
void lexer_jump_token(struct s_lexer *lexer);

/* File: lexer_processing.c */

/**
** @fn bool lexer_match_eof(struct s_lexer *lexer);
** @brief If the current value of the command string pointer equals to an EOF,
**        creates an EOF token and put it into the token list.
** @param The lexer instance.
** @return true if EOF is matched, false otherwise.
*/
bool lexer_match_eof(struct s_lexer *lexer);

/**
** @fn bool lexer_match_arith(struct s_lexer *lexer);
** @brief If the current value of the command string pointer equals to an EOF,
**        creates an EOF token and put it into the token list.
** @param The lexer instance.
** @return true if EOF is matched, false otherwise.
*/
bool lexer_match_arith(struct s_lexer *lexer);

/**
** @fn bool lexer_match_expansion(struct s_lexer *lexer);
** @brief If the current value of the command string pointer equals to an
**        expansion-type symbol - $((, $( or $ - , creates a token and put it
**        into the token list.
** @param The lexer instance.
** @return true if it matched, false otherwise.
*/
bool lexer_match_expansion(struct s_lexer *lexer);

/**
** @fn bool lexer_match_word(struct s_lexer *lexer);
** @brief If the current value of the command string pointer match to nothing
**        else, it's a word (command, parameter...), so it creates a token and
**        put it into the token list.
** @param The lexer instance.
** @return true if it matched, false otherwise.
*/
bool lexer_match_word(struct s_lexer *lexer);

/* File: lexer_match_operator.c */

/**
** @fn bool lexer_match_operator(struct s_lexer *lexer);
** @brief If the current value of the command string pointer match to an
**        operator - &, | ... -, creates a token and put it into the token
**        list.
** @param The lexer instance.
** @return true if it matched, false otherwise.
*/
bool lexer_match_operator(struct s_lexer *lexer);

/* File: lexer_match_symbol.c */

/**
** @fn bool lexer_match_and_or_not(struct s_lexer *lexer);
** @brief If the current value of the command string pointer match to an
**        AND, an OR or a NOT - &&, || or ! -, creates a token and put it into
**        the token list.
** @param The lexer instance.
** @return true if it matched, false otherwise.
*/
bool lexer_match_and_or_not(struct s_lexer *lexer);

/**
** @fn bool lexer_match_symbol(struct s_lexer *lexer);
** @brief If the current value of the command string pointer match to a
**        symbol - operator, redirection, IO, here-document... -, creates a
**        token and put it into the token list.
** @param The lexer instance.
** @return true if it matched, false otherwise.
*/
bool lexer_match_symbol(struct s_lexer *lexer);

/* File: lexer_quoting.c */

/**
** @fn bool lexer_match_quote(struct s_lexer *lexer);
** @brief If the current value of the command string pointer match to a
**        simple quote - ' -, it considers all its content as a whole
**        word, so it creates a word token and put it into the token list.
** @param The lexer instance.
** @return true if it matched, false otherwise.
*/
bool lexer_match_quote(struct s_lexer *lexer);

/**
** @fn bool lexer_match_dquote(struct s_lexer *lexer);
** @brief If the current value of the command string pointer match to a
**        double quote - " -, it considers all its content as a whole
**        word, but take into account every expansion, command call and
**        escaped values, so it creates a word token and put it into the token
**        list.
** @param The lexer instance.
** @return true if it matched, false otherwise.
*/
bool lexer_match_dquote(struct s_lexer *lexer);

#endif /* !LEXER_LEXER_H */
