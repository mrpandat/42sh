#include <ast.h>
#include <unistd.h>
#include <global.h>

int my_cd(struct s_simple_command_node *node)
{
    if (node->elements[1]->type == EL_WORD)
    {
        if (node->nb_elements < 2)
        {
            g_env.OLDPWD = g_env.PWD;
            g_env.PWD = g_env.HOME;
            chdir(g_env.HOME);
        }
        else if (strcmp(node->elements[1]->data.word, "-") == 0)
        {
            char *tmp = g_env.OLDPWD;
            g_env.OLDPWD = g_env.PWD;
            g_env.PWD = tmp;
            chdir(g_env.OLDPWD);
        }
        else
        {
            g_env.OLDPWD = g_env.PWD;
            g_env.PWD = node->elements[1]->data.word;
            chdir(node->elements[1]->data.word);
        }
        return 0;
    }
    return 1;
}