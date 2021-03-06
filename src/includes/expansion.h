/**
 ** @file expansion.h
 ** @brief Functions related to word expansion
 ** @author Moisan L
 */

#ifndef INC_42SH_EXPANSION_H
# define INC_42SH_EXPANSION_H
# include <ast.h>
# include <arith_lexer.h>

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
    enum e_arlex_type type;
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
    enum e_arlex_type type;
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

enum e_operand_type
{
    OPERAND_TOKEN,
    OPERAND_NODE
};

struct s_art_operand
{
    enum e_operand_type type;
    union
    {
        struct s_art_node *node;
        struct s_arlex_token *token;
    } data;
};

struct s_art_stack
{
    int size;
    struct s_art_operand **elements;
};

void add_stack(struct s_art_stack *stack, struct s_art_operand *operand);
struct s_art_operand *pop_stack(struct s_art_stack *stack);
struct s_art_operand *peek_stack(struct s_art_stack *stack);
struct s_art_stack *init_stack(void);
void free_stack(struct s_art_stack *stack);

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
 **
 ** @fn char *arithmetic_expansion(char *expression)
 ** @brief Calculate the result of an arithmetic expression
 ** @param expression The arithmetic expression
 ** @return A char* containing the result of the arithmetic calculation
 */
char *arithmetic_expansion(char *expression);
struct s_art_node *shunting_yard(struct s_arlex *lexer);

struct s_binop_node *init_binop_node(struct s_art_node *left,
                                     enum e_arlex_type type,
                                     struct s_art_node *right);
struct s_unop_node *init_unop_node(enum e_arlex_type type,
                                   struct s_art_node *son);
struct s_number_node *init_num_node_int(int num);
struct s_number_node *init_num_node_var(char *var);
struct s_art_node *init_art_node(void);
void free_binop_node(struct s_binop_node *node);
void free_unop_node(struct s_unop_node *node);
void free_num_node(struct s_number_node *node);
void free_art_node(struct s_art_node *node);
int execute_art_node(struct s_art_node *node);

char *expand_tilde(char *word);

/*
 ** @fn int variables(struct s_simple_command_node *node)
 ** @brief Save variables of a simple_command_node
 * ex: a=5 lol=45 lolmdr='mdr'
 ** @param node The command node
 ** @return Int: 0 if it's ok 1 if there is no variables of the command.
 */
int variables(struct s_simple_command_node *node);

/*
 ** @fn char *get_var(char *name)
 ** @brief Get a saved variable
 ** @param char* name the variable name
 ** @return Char: empty if no variable has been found, else, the value.
 */
char *get_var(char *name);
void set_var(char *var, void *value);


/*
 ** @fn int is_var_assign(char *word, int save)
 ** @brief Check if word is a assignement
 ** @param char* word, the assignement, int save 1 if you want to save the
 * variable assignement, 0 else.
 ** @return Int: 0 if it's ok 1 if there is no variables of the word.
 */
int is_var_assign(char *word, int save);

#endif //INC_42SH_EXPANSION_H
