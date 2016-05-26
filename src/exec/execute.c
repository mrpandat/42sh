#include <execute.h>
#include <util.h>

int execute(struct options opt)
{
    char **arguments = NULL;
    char *prog = NULL;
    if (strcmp(opt.command, "") != 0)
    {
        prog = args_from_str(opt.command, &arguments);
        int pid = fork();
        if (pid == 0)
            execve(prog, arguments, NULL);
        if (strcmp(opt.file, "") != 0)
            free(opt.command);
        free(arguments);
        free(prog);
    }
    return 0;
}

/*
 *  A && B && C sense : ==>
 *  A | B | C sens : <==
 *  A | B | c sens : pipe puis le &&
 */