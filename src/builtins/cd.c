#include <ast.h>
#include <unistd.h>
#include <global.h>
#include <util.h>

int cd_dir(struct s_simple_command_node *node)
{
    if (node->elements[1]->type == EL_WORD)
    {
        if (strcmp(node->elements[1]->data.word, "-") == 0)
        {
            char *tmp = g_env.OLDPWD;
            g_env.OLDPWD = g_env.PWD;
            g_env.PWD = tmp;
            chdir(g_env.OLDPWD);
        }
        else
        {
            if (file_test(node->elements[1]->data.word) == 33)
            {
                g_env.OLDPWD = g_env.PWD;
                g_env.PWD = node->elements[1]->data.word;
                chdir(node->elements[1]->data.word);
            }
            else
                return 1; // TODO : check if there is an error here
        }
    }
    printf("%s\n", g_env.PWD);
    return 0;
}

int my_cd(struct s_simple_command_node *node)
{
        if (node->nb_elements < 2)
        {
            g_env.OLDPWD = g_env.PWD;
            g_env.PWD = g_env.HOME;
            chdir(g_env.HOME);
            printf("%s\n", g_env.PWD);
            return 0;
        }
        else
            return cd_dir(node);
}