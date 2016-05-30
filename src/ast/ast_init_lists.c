#include "global.h"
#include "ast.h"

struct s_pipeline_node *init_pipeline_node(void)
{
    struct s_pipeline_node *node = malloc(sizeof (struct s_pipeline_node));
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
    struct s_and_or_node *node = malloc(sizeof (struct s_and_or_node));
    node->type = ANDOR_NONE;
    node->left = init_ast_node();
    node->right = NULL;
    return node;
}

struct s_list_node *init_list_node(void)
{
    struct s_list_node *node = malloc(sizeof (struct s_list_node));
    node->type = LIST_NONE;
    node->left = init_ast_node();
    node->right = NULL;
    return node;
}

