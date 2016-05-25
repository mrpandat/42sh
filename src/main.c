#include "includes/global.h"
#include "includes/argument_parser.h"


int main(int argc, char *argv[])
{
    struct options opt = {0, 0, 0, "", ""};
    if (argc < 2)
    {
        help(argv[0]);
        exit(0);
    }
    else
        parse_options(argc, argv, &opt, 1);
    if (strcmp(opt.command, "") == 0)
    {
        help(argv[0]);
        return -1;
    }
    char **arguments = NULL;
    char *save = malloc(sizeof (char) * strlen(opt.command) + 1);
    strcpy(save, opt.command);
    char *prog = strtok(opt.command, " ");
    int i = 0;
    char *arg = strtok(save, " ");

    while (arg != NULL)
    {
        arguments = realloc(arguments, sizeof (char *) * ++i);
        arguments[i - 1] = arg;
        arg = strtok(NULL, " ");
    }
    arguments = realloc(arguments, sizeof (char *) * (i+1));
    arguments[i] = 0;

    int pid = fork();
    if (pid == 0)
        execve(prog, arguments, NULL);

    free(arguments);
    free(save);
    return 0;
}

