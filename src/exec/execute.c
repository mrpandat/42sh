#include <execute.h>
#include <util.h>
#include <sys/stat.h>
#include <lexer.h>
#include <sys/wait.h>

int is_builtin(char *name) // add others when necessary
{
    if (strcmp(name, "exit") == 0)
        return 1;
    else if (strcmp(name, "echo") == 0)
        return 1;
    else if (strcmp(name, "cd") == 0)
        return 1;
    else if (strcmp(name, "source") == 0)
        return 1;
    return 0;
}



void not_found(char *name, char **arguments, struct options opt,
               struct s_ast_node *root, struct s_lexer *lexer)
{
    int res = file_test(name);
    if (res == 127|| res == 33)
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
        exit(127);
    }
}


int execute(struct options opt, struct s_ast_node *root, struct s_lexer *lexer)
{
    int ret = 0;
    if (strcmp(opt.command, "") != 0)
        ret = exec_ast_node(root);

    if (strcmp(opt.file, "") != 0)
        free(opt.command);

    free_ast_node(root);
    lexer_destroy(lexer);
    return ret;
}

int get_children_exit_status(int pid)
{
    int status = 0;
    waitpid(pid, &status, 0);
    return WEXITSTATUS(status);
}

/*
 *  A && B && C sens : ==>
 *  A | B | C sens : <==
 *  A | B | c sens : pipe puis le &&
 */
