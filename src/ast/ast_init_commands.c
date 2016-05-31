#include "global.h"
#include "ast.h"

struct s_funcdec_node *init_funcdec_node(char *name)
{
    struct s_funcdec_node *node = malloc(sizeof (struct s_funcdec_node));
    node->name = name;
    node->shell_command = init_ast_node();
    return node;
}

struct s_simple_command_node *init_simple_command_node(void)
{
    struct s_simple_command_node *node =
            malloc(sizeof (struct s_simple_command_node));
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

struct s_command_node *init_command_node(void)
{
    struct s_command_node *node = malloc(sizeof (struct s_command_node));
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
