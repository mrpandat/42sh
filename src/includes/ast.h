/**
 ** @file ast.h
 ** @brief Functions related to the AST part
 ** @author Moisan L
 */

#ifndef INC_42SH_AST_H
#define INC_42SH_AST_H

#include <stdbool.h>

struct s_if_node
{
    struct s_ast_node *predicate;
    struct s_ast_node *true_statement;
    struct s_ast_node *false_statement;
};

struct s_while_node
{
    struct s_ast_node *predicate;
    struct s_ast_node *statement;
};

struct s_until_node
{
    struct s_ast_node *predicate;
    struct s_ast_node *statement;
};

struct s_case_node
{
    char *word;
    int nb_items;
    struct s_case_item_node **items;
};

struct s_case_item_node
{
    char **words;
    int nb_words;
    struct s_ast_node *statement;
};

struct s_for_node
{
    char *iterator;
    char **words;
    int nb_words;
    struct s_ast_node *do_group;
};

struct s_redirection_node
{
    char *io_number;
    char *type;
    char *word;
};

struct s_funcdec_node
{
    char *name;
    struct s_ast_node *shell_command;
};

struct s_simple_command_node
{
    int nb_elements;
    struct s_element_node **elements;
};

enum e_element_type
{
    EL_NONE,
    EL_WORD,
    EL_ASSIGNEMENT_WORD,
    EL_REDIRECTION
};

union u_element_data
{
    char* word;
    char* assignement_word;
    struct s_redirection_node *s_redirection_node;
};

struct s_element_node
{
    enum e_element_type type;
    union u_element_data data;
};

struct s_command_node
{
    struct s_ast_node *content;
    int nb_redirections;
    struct s_redirection_node **redirections;
};

struct s_pipeline_node
{
    bool banged;
    int nb_commands;
    struct s_ast_node **commands;
};

enum e_and_or_type
{
    ANDOR_NONE,
    ANDOR_AND,
    ANDOR_OR
};

struct s_and_or_node
{
    enum e_and_or_type type;
    struct s_ast_node *left;
    struct s_ast_node *right;
};

enum e_list_type
{
    LIST_NONE,
    LIST_AND,
    LIST_SEMI,
    LIST_BG
};

struct s_list_node
{
    enum e_list_type type;
    struct s_ast_node *left;
    struct s_ast_node *right;
};

enum e_node_type
{
    ND_NONE,
    ND_IF,
    ND_COMMAND,
    ND_WHILE,
    ND_UNTIL,
    ND_CASE,
    ND_CASE_ITEM,
    ND_FOR,
    ND_REDIRECTION,
    ND_FUNCDEC,
    ND_SIMPLE_COMMAND,
    ND_PIPELINE,
    ND_AND_OR,
    ND_LIST
};

/**
 ** @struct s_ast_node
 ** @brief The generic ast node
 **
 ** @details This contains the type of the node (if_node, command_node...)
 **          and an union containing the data of the node
 */
struct s_ast_node
{
    enum e_node_type type; /*!< Type of the node */
    union
    {
        struct s_if_node *s_if_node;
        struct s_command_node *s_command_node;
        struct s_while_node *s_while_node;
        struct s_until_node *s_until_node;
        struct s_case_node *s_case_node;
        struct s_case_item_node *s_case_item_node;
        struct s_for_node *s_for_node;
        struct s_redirection_node *s_redirection_node;
        struct s_funcdec_node *s_funcdec_node;
        struct s_simple_command_node *s_simple_command_node;
        struct s_pipeline_node *s_pipeline_node;
        struct s_and_or_node *s_and_or_node;
        struct s_list_node *s_list_node;
    } data; /*!< Data of the node */
};

/* File: ast_init_utils.c */
struct s_ast_node* init_ast_node(void);
struct s_redirection_node *init_redirection_node(void);

/* File: ast_init_controls.c */
struct s_if_node *init_if_node(void);
struct s_case_node *init_case_node(char *word);
void add_case_item(struct s_case_node *node, struct s_case_item_node *item);
struct s_case_item_node *init_case_item_node(void);
void add_case_item_word(struct s_case_item_node *item, char *word);

/* File : ast_init_loops.c */
struct s_while_node *init_while_node(void);
struct s_until_node *init_until_node(void);
struct s_for_node *init_for_node(char *iterator);
void add_for_word(struct s_for_node *node, char *word);

/* File: ast_init_commands.c */
struct s_funcdec_node *init_funcdec_node(char *name);
struct s_simple_command_node *init_simple_command_node(void);
void add_simple_command_element(struct s_simple_command_node *node,
                                struct s_element_node *element);
struct s_command_node *init_command_node(void);
void add_command_redirection(struct s_command_node *command,
                             struct s_redirection_node *redirection);

/* File: ast_init_elements.c */
struct s_element_node *init_element_node(void);

/* File: ast_init_lists.c */
struct s_pipeline_node *init_pipeline_node(void);
void add_pipeline_command(struct s_pipeline_node *pipeline,
                          struct s_ast_node *command);
struct s_and_or_node *init_and_or_node(void);
struct s_list_node *init_list_node(void);

/* File: ast_free_utils.c */
void free_ast_node(struct s_ast_node* node);
void free_redirection_node(struct s_redirection_node *node);

/* File: ast_free_controls.c */
void free_if_node(struct s_if_node *node);
void free_case_node(struct s_case_node *node);
void free_case_item_node(struct s_case_item_node *node);

/* File: ast_free_loops.c */
void free_while_node(struct s_while_node *node);
void free_until_node(struct s_until_node *node);
void free_for_node(struct s_for_node *node);

/* File: ast_free_commands.c */
void free_funcdec_node(struct s_funcdec_node *node);
void free_simple_command_node(struct s_simple_command_node *node);
void free_command_node(struct s_command_node *node);

/* File: ast_free_elements.c */
void free_element_node(struct s_element_node *node);

/* File: ast_free_lists.c */
void free_pipeline_node(struct s_pipeline_node *node);
void free_and_or_node(struct s_and_or_node *node);
void free_list_node(struct s_list_node *node);



#endif /* !INC_42SH_AST_H */
