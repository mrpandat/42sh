#include <global.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <util.h>
#include "../includes/execute.h"


struct process *read_process(struct process *pro)
{
    pro->stdout_contents = path_to_str("out");
    pro->stderr_contents = path_to_str("err");
    unlink("out");
    unlink("err");
    return pro;
}

void free_process(struct process *pro)
{
    free(pro->stdout_contents);
    free(pro->stdout_contents);
    free(pro);
}

struct process *exec_command(struct s_ast_node *node)
{
    // todo : check that they don't already exists
    int fd_out = open("out", O_CREAT | O_RDWR,
                  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
    int fd_err = open("err", O_CREAT | O_RDWR,
                  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
    // duplicate to restore for later use
    int oldout = dup(STDOUT_FILENO);
    int olderr = dup(STDERR_FILENO);
    // go to file
    dup2(fd_out, 1);
    dup2(fd_err, 2);
    close(fd_out);
    close(fd_err);
    struct process *pro = malloc(sizeof (struct process));
    pro->ret = exec_ast_node(node);

    fflush(stdout);
    fflush(stderr);
    pro->stdout_contents = path_to_str("out");
    pro->stderr_contents = path_to_str("err");
    unlink("out");
    unlink("err");
    //pro = read_process(pro);
    // back to terminal
    dup2(oldout, 1);
    dup2(olderr, 2);
    return pro;
}



int exec_pipeline_node(struct s_pipeline_node *node)
{
    if (node->nb_commands > 1)
    {
        int ret = 0;
        // TODO: Handle banged pipeline

            //TODO : handle redirection to next one
        for (int i = 0; i < node->nb_commands; i++)
            ret =  exec_command(node->commands[i])->ret;

        return ret;
    } else if (node-> nb_commands == 1)
        return exec_ast_node(node->commands[0]);
    else
        return 1;
}




int exec_and_or_node(struct s_and_or_node *node)
{
    if (node->type == ANDOR_NONE)
        return exec_ast_node(node->left);
    else if (node->type == ANDOR_OR)
        return !(!exec_ast_node(node->left) || !exec_ast_node(node->right));
    else if (node->type == ANDOR_AND)
        return !(!exec_ast_node(node->left) && !exec_ast_node(node->right));
    return -1;
}

static int exec_list_and_node(struct s_list_node *node)
{
    int pid = fork();
    if (pid == 0)
    {
        exec_ast_node(node->right);
        return 0;
    }
    else
    {
        exec_ast_node(node->left);
        wait(NULL);
        return 0;
    }
}

int exec_list_node(struct s_list_node *node)
{
    if (node->type == LIST_SEMI)
    {
        exec_ast_node(node->left);
        return exec_ast_node(node->right);
    }
    else if (node->type == LIST_AND)
        return exec_list_and_node(node);
    else if (node->type == LIST_BG)
    {
        int pid = fork();
        if (pid == 0)
            return exec_ast_node(node->left);
        else
            return 0;
    }
    else if (node->type == LIST_NONE)
        return exec_ast_node(node->left);
    else
        return -1;
}
