#include <malloc.h>
#include <execute.h>
#include <util.h>


int my_source(struct s_simple_command_node *node)
{
    int res = 0;
    if (node->elements[0]->type == EL_WORD
        && node->elements[1]->type == EL_WORD)
    {
        char *prog = "./42sh";
        char **arguments = calloc(3, sizeof(char *));
        arguments[0] = malloc(sizeof(char) * (strlen(prog) + 1));
        arguments[1] = malloc(
                sizeof(char) * (strlen(node->elements[1]->data.word) + 1));
        strcpy(arguments[1], node->elements[1]->data.word);
        strcpy(arguments[0], prog);
        if (res == 0)
        {
            if ((res = fork()) == 0)
                execve(prog, arguments, NULL);
            res = get_children_exit_status(res);
        }
        free(arguments[0]);
        free(arguments[1]);
        free(arguments);
    }
    return res;
}


