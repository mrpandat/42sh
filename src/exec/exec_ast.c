#include <global.h>
#include "../includes/execute.h"

int exec_ast_node(struct s_ast_node *node)
{
    if (node == NULL)
        return -1;
    enum e_node_type type = node->type;
    if (type == ND_IF)
        return exec_if_node(node->data.s_if_node);
    else if (type == ND_COMMAND)
        return exec_command_node(node->data.s_command_node);
    else if (type == ND_WHILE)
        return exec_while_node(node->data.s_while_node);
    else if (type == ND_UNTIL)
        return exec_until_node(node->data.s_until_node);
    else if (type == ND_CASE)
        return exec_case_node(node->data.s_case_node);
    else if (type == ND_CASE_ITEM)
        return exec_case_item_node(node->data.s_case_item_node);
    else if (type == ND_FOR)
        return exec_for_node(node->data.s_for_node);
    else if (type == ND_REDIRECTION)
        return exec_redirection_node(node->data.s_redirection_node);
    else if (type == ND_FUNCDEC)
        return exec_funcdec_node(node->data.s_funcdec_node);
    else if (type == ND_SIMPLE_COMMAND)
        return exec_simple_command_node(node->data.s_simple_command_node);
    else if (type == ND_PIPELINE)
        return exec_pipeline_node(node->data.s_pipeline_node);
    else if (type == ND_AND_OR)
        return exec_and_or_node(node->data.s_and_or_node);
    else if (type == ND_LIST)
        return exec_list_node(node->data.s_list_node);
    return -1;
}

int exec_if_node(struct s_if_node *node)
{
    int ret = 0;
    if (exec_ast_node(node->predicate))
        ret = exec_ast_node(node->true_statement);
    else
    {
        if (node->false_statement != NULL)
            ret = exec_ast_node(node->false_statement);
    }
    return ret;
}

int exec_while_node(struct s_while_node *node)
{
    int ret = 0;
    while (exec_ast_node(node->predicate))
        ret = exec_ast_node(node->statement);
    return ret;
}

int exec_until_node(struct s_until_node *node)
{
    int ret = 0;
    while (!exec_ast_node(node->predicate))
        ret = exec_ast_node(node->statement);
    return ret;
}

int exec_case_node(struct s_case_node *node)
{
    // TODO: Implement case loop
    if (node == NULL)
        return -1;
    return -1;
}

int exec_case_item_node(struct s_case_item_node *node)
{
    // TODO: Implement case item
    if (node == NULL)
        return -1;
    return -1;
}

int exec_for_node(struct s_for_node *node)
{
    // TODO: Implement for loop
    if (node == NULL)
        return -1;
    return -1;
}

int exec_redirection_node(struct s_redirection_node *node)
{
    // TODO: Implement redirection
    if (node == NULL)
        return -1;
    return -1;
}

int exec_funcdec_node(struct s_funcdec_node *node)
{
    // TODO: Implement function definition
    if (node == NULL)
        return -1;
    return -1;
}

int exec_simple_command_node(struct s_simple_command_node *node)
{
    char *word = node->elements[0]->data.word;
    char *prog =  malloc(sizeof (char) * strlen(word) + 1);
    char **arguments = calloc(node->nb_elements + 1, sizeof(char *));
    for (int i = 0; i < node->nb_elements; i++)
    {
        if (node->elements[i]->type == EL_WORD)
        {
            word = node->elements[i]->data.word;
            if (i == 0)
                strcpy(prog, word);
            arguments[i] = malloc(sizeof (char) * (strlen(word) + 1));
            strcpy(arguments[i], word);
        }
    }

    int res = file_test(prog);
    if (res == 0)
    {
        int pid = fork();
        if (pid == 0)
            execve(prog, arguments, NULL);

        res = get_children_exit_status(pid);
    }
    for (int i = 0; i < node->nb_elements; i++)
        free(arguments[i]);
    free(arguments);
    free(prog);
    return res;
}

int exec_command_node(struct s_command_node *node)
{
    // TODO: Handle redirections
    return exec_ast_node(node->content);
}

int exec_pipeline_node(struct s_pipeline_node *node)
{
    // TODO: Handle banged pipeline
    if (node->nb_commands > 0)
        return exec_ast_node(node->commands[0]); // TODO: Execute all commands
    return -1;
}

int exec_and_or_node(struct s_and_or_node *node)
{
    if (node->type == ANDOR_NONE)
        return exec_ast_node(node->left);
    else if (node->type == ANDOR_OR)
        return exec_ast_node(node->left) || exec_ast_node(node->right);
    else if (node->type == ANDOR_AND)
        return exec_ast_node(node->left) && exec_ast_node(node->right);
    return -1;
}

int exec_list_node(struct s_list_node *node)
{
    if (node->type == LIST_SEMI)
    {
        exec_ast_node(node->left);
        return exec_ast_node(node->right);
    }
    else if (node->type == LIST_AND)
    {
        int pid = fork();
        if (pid == 0)
        {
            exec_ast_node(node->right);
            return 0;
        }
        else
        {
            exec_ast_node(node->left);
            wait(NULL);
            return 0;
        }
    }
    else if (node->type == LIST_NONE)
        return exec_ast_node(node->left);
    else
        return -1;
}
