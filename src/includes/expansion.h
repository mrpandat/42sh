/**
 ** @file expansion.h
 ** @brief Functions related to word expansion
 ** @author Moisan L
 */

#ifndef INC_42SH_EXPANSION_H
# define INC_42SH_EXPANSION_H

enum e_binop_type
{
    BINOP_MINUS,
    BINOP_ADD,
    BINOP_MULT,
    BINOP_DIV,
    BINOP_POW,
    BINOP_BIT_AND,
    BINOP_BIT_OR,
    BINOP_BIT_XOR,
    BINOP_BOOL_AND,
    BINOP_BOOL_OR,
};

struct s_binop_node
{
    enum e_binop_type type;
    struct s_art_node *left;
    struct s_art_node *right;
};

enum e_unop_type
{
    UNOP_MINUS,
    UNOP_ADD,
    UNOP_BANG,
    UNOP_INV
};

struct s_unop_node
{
    enum e_unop_type type;
    struct s_art_node *number;
};

enum e_number_type
{
    NUM_INT,
    NUM_VAR
};

struct s_number_node
{
    enum e_number_type type;
    union
    {
        char *variable;
        int integer;
    } data;
};

enum e_art_node_type
{
    ART_BINOP,
    ART_UNOP,
    ART_NUM
};

struct s_art_node
{
    enum e_art_node_type type;
    union
    {
        struct s_binop_node *binop;
        struct s_unop_node *unop;
        struct s_number_node *number;
    } data;
};

struct s_stream
{
    char *content;
    int pos;
};

char *stream_peek(struct s_stream *stream);
void stream_read(struct s_stream *stream, int n);
char* expand_path(char * path);

/**
 **
 ** Read an AST from string
 **
 ** The operators handled are below, ranked by priority:
 **   - '+', '-' (unary minus and plus)
 **   - '!', '~' (logical and bitwise negation)
 **   - '**'     (exponentiation)
 **   - '*', '/' (multiplication, division)
 **   - '+', '-' (addition, subtraction)
 **   - '&'      (bitwise AND)
 **   - '^'      (bitwise XOR)
 **   - '|'      (bitwise OR)
 **   - '&&'     (logical AND)
 **   - '||'     (logical OR)
 **   - '(', ')' (for grouping)
 **
 ** The LL grammar used is the following:
 **
 **   J := I
 **      | I '||' J
 **
 **   I := H
 **      | H '&&' I
 **
 **   H := G
 **      | G '|' H
 **
 **   G := F
 **      | F '^' G
 **
 **   F := E
 **      | E '&' F
 **
 **   E := D
 **      | D '+' E
 **      | D '-' E
 **
 **   D := C
 **      | C '*' D
 **      | C '/' D
 **
 **   C := B
 **      | B '**' C
 **
 **   B := A
 **      | '(' J ')'
 **      | '!' B
 **      | '~' B
 **
 **   A := number
 **      | '(' J ')'
 **      | '-' A
 **      | '+' A
 **
 ** @fn char *arithmetic_expansion(char *expression)
 ** @brief Calculate the result of an arithmetic expression
 ** @param expression The arithmetic expression
 ** @return A char* containing the result of the arithmetic calculation
 */
char *arithmetic_expansion(char *expression);
struct s_art_node *read_a(struct s_stream *stream);
struct s_art_node *read_b(struct s_stream *stream);
struct s_art_node *read_c(struct s_stream *stream);
struct s_art_node *read_d(struct s_stream *stream);
struct s_art_node *read_e(struct s_stream *stream);
struct s_art_node *read_f(struct s_stream *stream);
struct s_art_node *read_g(struct s_stream *stream);
struct s_art_node *read_h(struct s_stream *stream);
struct s_art_node *read_i(struct s_stream *stream);
struct s_art_node *read_j(struct s_stream *stream);
struct s_art_node *read_num(struct s_stream *stream);
void read_spaces(struct s_stream *stream);
struct s_binop_node *init_binop_node(struct s_art_node *left,
                                     enum e_binop_type type,
                                     struct s_art_node *right);
struct s_unop_node *init_unop_node(enum e_unop_type type,
                                   struct s_art_node *son);
struct s_number_node *init_num_node_int(int num);
struct s_art_node *init_art_node(void);
void free_binop_node(struct s_binop_node *node);
void free_unop_node(struct s_unop_node *node);
void free_num_node(struct s_number_node *node);
void free_art_node(struct s_art_node *node);
int execute_art_node(struct s_art_node *node);

char *expand_tilde(char *word);

#endif //INC_42SH_EXPANSION_H
