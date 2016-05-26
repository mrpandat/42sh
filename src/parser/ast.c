#include "../includes/global.h"
#include "../includes/ast.h"

struct s_ast_node *init_ast_node(void)
{
    return malloc(sizeof (struct s_ast_node));
}

struct s_if_node *init_if_node(void)
{
    struct s_if_node *node = malloc(sizeof (struct s_if_node *));
    node->false_statement = init_ast_node();
    node->true_statement = init_ast_node();
    node->predicate = init_ast_node();
    return node;
}

struct s_while_node *init_while_node(void)
{
    struct s_while_node *node = malloc(sizeof (struct s_while_node *));
    node->predicate = init_ast_node();
    node->statement = init_ast_node();
    return node;
}

struct s_until_node *init_until_node(void)
{
    struct s_until_node *node = malloc(sizeof (struct s_until_node *));
    node->predicate = init_ast_node();
    node->statement = init_ast_node();
    return node;
}

struct s_case_node *init_case_node(char *word)
{
    struct s_case_node *node = malloc(sizeof (struct s_case_node *));
    node->word = word;
    node->nb_items = 0;
    node->items = NULL;
    return node;
}

void add_case_item(struct s_case_node *node, struct s_case_item_node *item)
{
    node->nb_items++;
    node->items = realloc(node->items,
                          node->nb_items * sizeof (struct s_case_item_node *));
    node->items[node->nb_items - 1] = item;
}

struct s_case_item_node *init_case_item_node(void)
{
    struct s_case_item_node *node = malloc(sizeof (struct s_case_item_node *));
    node->nb_words = 0;
    node->statement = init_ast_node();
    node->words = NULL;
    return node;
}

void add_case_item_word(struct s_case_item_node *item, char *word)
{
    item->nb_words++;
    item->words = realloc(item->words, item->nb_words * sizeof (char *));
    item->words[item->nb_words - 1] = word;
}

struct s_for_node *init_for_node(char *iterator)
{
    struct s_for_node *node = malloc(sizeof (struct s_for_node *));
    node->iterator = iterator;
    node->nb_words = 0;
    node->words = NULL;
    node->do_group = init_ast_node();
    return node;
}

void add_for_word(struct s_for_node *node, char *word)
{
    node->nb_words++;
    node->words = realloc(node->words, node->nb_words * sizeof (char *));
    node->words[node->nb_words - 1] = word;
}

struct s_redirection_node *init_redirection_node(void)
{
    struct s_redirection_node *node =
            malloc(sizeof (struct s_redirection_node *));
    node->io_number = NULL;
    node->type = NULL;
    node->word = NULL;
    return node;
}

struct s_funcdec_node *init_funcdec_node(char *name)
{
    struct s_funcdec_node *node = malloc(sizeof (struct s_funcdec_node *));
    node->name = name;
    node->shell_command = init_ast_node();
    return node;
}

struct s_simple_command_node *init_simple_command_node(void)
{
    struct s_simple_command_node *node =
            malloc(sizeof (struct s_simple_command_node *));
    node->nb_elements = 0;
    node->elements = NULL;
    return node;
}

void add_simple_command_element(struct s_simple_command_node *node,
                                struct s_element_node *element)
{
    node->nb_elements++;
    node->elements = realloc(node->elements,
                             node->nb_elements
                             * sizeof (struct s_element_node *));
    node->elements[node->nb_elements - 1] = element;
}

struct s_element_node *init_element_node(void)
{
    struct s_element_node *node = malloc(sizeof (struct s_element_node *));
    node->type = EL_NONE;
    return node;
}

struct s_command_node *init_command_node(void)
{
    struct s_command_node *node = malloc(sizeof (struct s_command_node *));
    node->content = init_ast_node();
    node->nb_redirections = 0;
    node->redirections = NULL;
    return node;
}

void add_command_redirection(struct s_command_node *command,
                             struct s_redirection_node *redirection)
{
    command->nb_redirections++;
    command->redirections = realloc(command->redirections,
                             command->nb_redirections
                             * sizeof (struct s_redirection_node *));
    command->redirections[command->nb_redirections - 1] = redirection;
}

struct s_pipeline_node *init_pipeline_node(void)
{
    struct s_pipeline_node *node = malloc(sizeof (struct s_pipeline_node *));
    node->banged = false;
    node->nb_commands = 0;
    node->commands = NULL;
    return node;
}

void add_pipeline_command(struct s_pipeline_node *pipeline,
                          struct s_ast_node *command)
{
    pipeline->nb_commands++;
    pipeline->commands = realloc(pipeline->commands,
                                     pipeline->nb_commands
                                    * sizeof (struct s_ast_node *));
    pipeline->commands[pipeline->nb_commands - 1] = command;
}

struct s_and_or_node *init_and_or_node(void)
{
    struct s_and_or_node *node = malloc(sizeof (struct s_and_or_node *));
    node->type = ND_IF_NONE;
    node->left = init_ast_node();
    node->right = NULL;
    return node;
}

struct s_list_node *init_list_node(void)
{
    struct s_list_node *node = malloc(sizeof (struct s_list_node *));
    node->type = ND_LIST_NONE;
    node->left = init_ast_node();
    node->right = NULL;
    return node;
}

