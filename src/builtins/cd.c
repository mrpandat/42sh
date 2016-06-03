#include <ast.h>
#include <unistd.h>
#include <global.h>

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
        {
            if (node->elements[1]->type == EL_WORD)
            {
                if (strcmp(node->elements[1]->data.word, "-") == 0)
                {
                    char *tmp = g_env.OLDPWD;
                    g_env.OLDPWD = g_env.PWD;
                    g_env.PWD = tmp;
                    chdir(g_env.OLDPWD);
                    printf("%s\n", g_env.PWD);
                }
                else
                {
                    g_env.OLDPWD = g_env.PWD;
                    g_env.PWD = node->elements[1]->data.word;
                    chdir(node->elements[1]->data.word);
                    printf("%s\n", g_env.PWD);
                }
            }

            return 0;
        }
    return 1;
}