#include <execute.h>
#include <util.h>
#include <sys/stat.h>

int execute(struct options opt)
{
    char **arguments = NULL;
    char *prog = NULL;
    if (strcmp(opt.command, "") != 0)
    {
        prog = args_from_str(opt.command, &arguments);

        // TODO @drov refactor all this please

        if (NULL == fopen(prog, "r+"))
        {
            // File does not exist
            // TODO Check if error code is valid
            return 168;
        }

        struct stat sb;
        if (stat(prog, &sb) == 0 && !(sb.st_mode & S_IXUSR))
        {
            // File is not executable
            // TODO Check if error code is valid
            return 199;
        }

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