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
    struct s_ast_node **items;
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
    EL_WORD,
    EL_ASSIGNEMENT_WORD,
    EL_REDIRECTION
};

struct s_element_node
{
    enum e_element_type type;
    union
    {
        char* word;
        char* assignement_word;
        struct s_ast_node *s_redirection_node;
    } data;
};

struct s_command_node
{
    struct s_ast_node *content;
    int nb_redirections;
    struct s_ast_node **redirections;
};

struct s_pipeline_node
{
    bool banged;
    int nb_commands;
    struct s_ast_node **commands;
};

enum e_and_or_type
{
    ND_AND_IF,
    ND_OR_IF,
    ND_IF_NONE
};

struct s_and_or_node
{
    enum e_and_or_type type;
    struct s_ast_node *left;
    struct s_ast_node *right;
};

enum e_list_type
{
    ND_AND,
    ND_OR,
    ND_LIST_NONE
};

struct s_list_node
{
    enum e_list_type type;
    struct s_ast_node *left;
    struct s_ast_node *right;
};

enum e_node_type
{
    ND_IF,
    ND_WORD,
    ND_PREDICATE,
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

struct s_ast_node
{
    enum e_node_type type;
    union
    {
        struct s_if_node *s_if_node;
        struct s_word_node *s_word_node;
        struct s_predicate_node *s_predicate_node;
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
    } data;
};

struct s_ast_node* init_ast_node(void);

#endif /* !INC_42SH_AST_H */
