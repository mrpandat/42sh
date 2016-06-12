#include <stdlib.h>
#include <execute.h>
#include <util.h>
#include <global.h>


int my_source(struct s_simple_command_node *node)
{
    int res = 0;
    if (node->elements[0]->type == EL_WORD
        && node->elements[1]->type == EL_WORD)
    {
        char *prog = "./42sh";
        char **arguments = calloc(3, sizeof(char *));
        char *word = exec_word(node->elements[1]->data.s_word);
        arguments[0] = malloc(sizeof(char) * (strlen(prog) + 1));
        arguments[1] = malloc(sizeof(char) * (strlen(word) + 1));
        strcpy(arguments[1], word);
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


