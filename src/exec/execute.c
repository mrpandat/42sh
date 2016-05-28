#include <execute.h>
#include <util.h>
#include <sys/stat.h>

int file_test(char *name)
{
    struct stat *stats = malloc(sizeof (struct stat));
    int res = 0;
    if (stat(name, stats) > -1)
    {
        if (S_ISREG(stats->st_mode))
            res = 0;
        else
            res = 127;
    }
    else
        res = 127;
    if (res == 0 && !(stats->st_mode & S_IXUSR))
        res = 126;
    free(stats);

    return res;
}

void children(char *prog, char **arguments, struct options opt)
{
    int res = file_test(prog);
    if (res != 0)
    {
        free(arguments);
        free(prog);
        if (strcmp(opt.file, "") != 0)
            free(opt.command);
        exit(res);
    }
    execve(prog, arguments, NULL);
}

int execute(struct options opt)
{
    char **arguments = NULL;
    char *prog = NULL;
    if (strcmp(opt.command, "") != 0)
    {
        prog = args_from_str(opt.command, &arguments);
        int res = file_test(prog);
        if (res != 0)
            exit(res);
        int pid = fork();
        if (pid == 0)
            children(prog, arguments, opt);
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
