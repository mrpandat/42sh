#include <builtins.h>

int execute_long_option(struct s_simple_command_node *node, int i, int options) {
    if (node->nb_elements == 2)
    {
        if (!strcmp("--version", node->elements[i]->data.word)
            && options == 0)
        {
            printf("Version: 0.1\n");
            return 0;
        }
        if (!strcmp("--help", node->elements[i]->data.word)
            && options == 0)
        {
            printf("Version: 0.1.\n Ecrit par Treibert "
                           "Jean.\n");
            return 0;
        }
    }
    return 1;
}

int my_echo(struct s_simple_command_node *node)
{
    int words = 0;
    int options = 0;
    int noption = 0;
    int eoption = 0;
    int Eoption = 0;
    for (int i = 1; i < node->nb_elements; i++)
    {
        if (node->elements[i]->type == EL_WORD)
        {
            if (words == 0)
            {
                if(execute_long_option(node, i, options))
                    return 0;

                if (!strcmp("-n", node->elements[i]->data.word) && noption == 0)
                {
                    noption = 1;
                    options++;
                    continue;
                }
                else if (!strcmp("-e", node->elements[i]->data.word) && Eoption
                                                                        == 0)
                {
                    Eoption = 1;
                    options++;
                    continue;
                }
                else if (!strcmp("-E", node->elements[i]->data.word) && eoption
                                                                        == 0)
                {
                    eoption = 1;
                    options++;
                    continue;
                }

            }

            if (words != 0)
                printf(" ");
            printf("%s", node->elements[i]->data.word);
            words++;
        }
    }
    if (noption == 0)
        putchar('\n');
    return 0;
}
