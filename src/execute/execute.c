#include <execute.h>

int execute(struct options opt)
{
    char **arguments = NULL;
    char *save = malloc(sizeof(char) * strlen(opt.command) + 1);
    strcpy(save, opt.command);
    char *prog = strtok(opt.command, " ");
    int i = 0;
    char *arg = strtok(save, " ");

    while (arg != NULL)
    {
        arguments = realloc(arguments, sizeof(char *) * ++i);
        arguments[i - 1] = arg;
        arg = strtok(NULL, " ");
    }
    arguments = realloc(arguments, sizeof(char *) * (i + 1));
    arguments[i] = 0;

    int pid = fork();
    if (pid == 0)
        execve(prog, arguments, NULL);

    free(arguments);
    free(save);
    return 0;
}