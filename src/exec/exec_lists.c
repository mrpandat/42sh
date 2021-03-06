#include <global.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <util.h>
#include <ast.h>
#include "../includes/execute.h"

int exec_pipeline_node(struct s_pipeline_node *node)
{
    if (node-> nb_commands > 0)
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
