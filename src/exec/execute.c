#include <execute.h>
#include <util.h>
#include <sys/stat.h>
#include <lexer.h>

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


void not_found(char *name, char **arguments, struct options opt,
               struct s_ast_node *root, struct s_lexer *lexer)
{
    int res = file_test(name);
    if (res == 127)
    {
        char *message = str_append("/bin/sh: ", name);
        char *message1 = str_append(message, ": command not found");
        fprintf(stderr, "%s\n", message1);

        if (strcmp(opt.file, "") != 0)
            free(opt.command);
        free_ast_node(root);
        lexer_destroy(lexer);
        free(message);
        free(message1);
        free(name);
        free(arguments);
        exit(res);
    }
}

int execute(struct options opt, struct s_ast_node *root, struct s_lexer *lexer)
{
    char **arguments = NULL;
    char *prog = NULL;
    if (strcmp(opt.command, "") != 0)
    {
        prog = args_from_str(opt.command, &arguments);
        not_found(prog, arguments, opt, root, lexer);
        int pid = fork();
        if (pid == 0)
            execve(prog, arguments, NULL);
        if (strcmp(opt.file, "") != 0)
            free(opt.command);
        free(arguments);
        free(prog);
        free_ast_node(root);
        lexer_destroy(lexer);
    }
    return 0;
}

/*
 *  A && B && C sens : ==>
 *  A | B | C sens : <==
 *  A | B | c sens : pipe puis le &&
 */
