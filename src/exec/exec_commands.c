#include <global.h>
#include <builtins.h>
#include "../includes/execute.h"

int exec_funcdec_node(struct s_funcdec_node *node)
{
    // TODO: Implement function definition
    if (node == NULL)
        return -1;
    return -1;
}

char **get_argv(struct s_simple_command_node *node,
              char **prog)
{
    char **arguments = calloc(node->nb_elements + 1, sizeof(char *));
    char *word = NULL;
    for (int i = 0; i < node->nb_elements; i++)
    {
        if (node->elements[i]->type == EL_WORD)
        {
            word = node->elements[i]->data.word;
            if (i == 0)
                strcpy(*prog, word);
            arguments[i] = malloc(sizeof (char) * (strlen(word) + 1));
            strcpy(arguments[i], word);
        }
    }

    return arguments;
}

int exec_file(struct s_simple_command_node *node)
{
    char *prog =  malloc(sizeof (char) *
                         strlen(node->elements[0]->data.word) + 1);
    char **arguments = get_argv(node, &prog);
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

int exec_builtin(struct s_simple_command_node *node)
{
    if (!strcmp("echo", node->elements[0]->data.word))
    {
        return my_echo(node);
    }
    else if (!strcmp("exit", node->elements[0]->data.word))
    {
        if (node->nb_elements < 2)
            return 1;
        my_exit(atoi(node->elements[1]->data.word));
    }
    return 1;
}

int exec_simple_command_node(struct s_simple_command_node *node)
{
    if (is_builtin(node->elements[0]->data.word) == 1)
        return exec_builtin(node);
    else
        return exec_file(node);
}

int exec_command_node(struct s_command_node *node)
{
    // TODO: Handle redirections
    return exec_ast_node(node->content);
}
