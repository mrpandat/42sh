#include <execute.h>

int execute(struct options opt)
{
    args_from_str()
    int pid = fork();
    if (pid == 0)
        execve(prog, arguments, NULL);

    free(arguments);
    free(save);
    return 0;
}