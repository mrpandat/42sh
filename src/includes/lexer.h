#ifndef LEXER_LEXER_H
# define LEXER_LEXER_H

# include "../includes/global.h"

enum e_token_type
{
    TK_UNDEFINED, /** Type to be defined */
            TK_AND, /** & (bitwise operation) */
            TK_OR, /** | (bitwise operation) */
            TK_AND_IF, /** && */
            TK_OR_IF, /** || */
            TK_NEWLINE, /** \n */
            TK_EOF, /** \0 */
            TK_SEMI, /** ; */
            TK_DSEMI, /** ;; */
            TK_BANG, /** ! */
            TK_LEXPR, /** $( */
            TK_LPAR, /** ( */
            TK_RPAR, /** ) */
            TK_LBRACE, /** { */
            TK_RBRACE, /** } */
            TK_GREAT, /** > */
            TK_DGREAT, /** >> */
            TK_LESS, /** < */
            TK_DLESS, /** << */
            TK_DLESSDASH, /** <<- */
            TK_GREATAND, /** >& */
            TK_LESSAND, /** <& */
            TK_CLOBBER, /** >| */
            TK_LESSGREAT, /** <> */
            TK_LARITH, /** $(( */
            TK_RARITH, /** )) */
            TK_WORD, /** (a-zA-Z_)[(a-zA-Z0-9_)]* */
            TK_IF, /** "if" */
            TK_THEN, /** "then" */
            TK_ELSE, /** "else" */
            TK_ELIF, /** "elif" */
            TK_FI, /** "fi" */
            TK_DO, /** "do" */
            TK_DONE, /** "done" */
            TK_CASE, /** "case" */
            TK_ESAC, /** "esac" */
            TK_WHILE, /** "while" */
            TK_UNTIL, /** "until" */
            TK_FOR, /** "for" */
            TK_IN, /** "in" */
            TK_IONUMBER, /** 0, 1 or 2 */
            TK_HEREDOC,
            TK_FUNCTION,
            TK_ASSIGNEMENT
};

/**
** @brief   Represents a Lexer token implemented as a linked list, with a type
**          and a value.
**
** @author  Thomas Domingues
*/
struct s_lexer_token
{
    enum e_token_type type;
    char *value;
    struct s_lexer_token *next;
};

struct s_lexer
{
    char *command;
    char *current;
    struct s_lexer_token *tk_list;
    struct s_lexer_token *tk_current;
};

/* File: lexer.c */

struct s_lexer *lexer_init(const char *command);

int lexer_current_position(struct s_lexer *lexer);

void lexer_process(struct s_lexer *lexer);

bool lexer_match_expr(struct s_lexer *lexer);

void lexer_destroy(struct s_lexer *lexer);

/* File: lexer_tokening.c */

void lexer_add_token(struct s_lexer *lexer, enum e_token_type type, char *val);

struct s_lexer_token *lexer_peek(struct s_lexer *lexer);

struct s_lexer_token *lexer_read(struct s_lexer *lexer);

struct s_lexer_token *lexer_next_token(struct s_lexer *lexer);

void lexer_jump_token(struct s_lexer *lexer);

/* File: lexer_processing.c */

bool lexer_match_eof(struct s_lexer *lexer);

bool lexer_match_arith(struct s_lexer *lexer);

bool lexer_match_expansion(struct s_lexer *lexer);

bool lexer_match_word(struct s_lexer *lexer);

/* File: lexer_match_operator.c */

bool lexer_match_operator(struct s_lexer *lexer);

/* File: lexer_match_symbol.c */

bool lexer_match_and_or_not(struct s_lexer *lexer);

bool lexer_match_symbol(struct s_lexer *lexer);

/* File: lexer_utils.c */

void print_lexer(struct s_lexer *lexer);

void print_token_list(struct s_lexer *lexer);

void print_token(struct s_lexer_token *token);

#endif /* !LEXER_LEXER_H */
