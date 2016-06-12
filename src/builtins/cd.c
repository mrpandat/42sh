#include <ast.h>
#include <unistd.h>
#include <global.h>
#include <util.h>
#include <execute.h>

int cd_dir(struct s_simple_command_node *node)
{
    if (node->elements[1]->type == EL_WORD)
    {
        if (strcmp(exec_word(node->elements[1]->data.s_word), "-") == 0)
        {
            char *tmp = g_env.OLDPWD;
            g_env.OLDPWD = g_env.PWD;
            g_env.PWD = tmp;
            chdir(g_env.PWD);
            printf("%s", g_env.PWD);
        }
        else
        {
            if (file_test(exec_word(node->elements[1]->data.s_word)) == 33)
            {
                g_env.OLDPWD = g_env.PWD;
                g_env.PWD = exec_word(node->elements[1]->data.s_word);
                chdir(exec_word(node->elements[1]->data.s_word));
            }
            else
            {
                return 2;
            }
        }
    }
    return 0;
}

int my_cd(struct s_simple_command_node *node)
{
        if (node->nb_elements < 2)
        {
            g_env.OLDPWD = g_env.PWD;
            g_env.PWD = g_env.HOME;
            chdir(g_env.HOME);
            return 0;
        }
        else
            return cd_dir(node);
}
