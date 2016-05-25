#include "../includes/global.h"

void args_from_str(char *str, char **arguments, char *prog)
{
    char *save = malloc(sizeof(char) * strlen(str) + 1);
    strcpy(save, str);
    prog = strtok(str, " ");
    int i = 0;
    char *arg = strtok(save, " ");

    while (arg != NULL)
    {
        arguments = realloc(arguments, sizeof(char *) * ++i);
        arguments[i - 1] = arg;
        arg = strtok(NULL, " ");
    }
    arguments = realloc(arguments, sizeof(char *) * (i + 1));
    arguments[i] = 0;
}

char *str_append(char *str_one, char *str_two)
{
    char *str;
    if ((str = malloc(strlen(str_one) + strlen(str_two) + 1)) != NULL
        && (str[0] = '\0') == '\0')
    {
        strcat(str, str_one);
        strcat(str, str_two);
    }
    else
        fprintf(stderr, "Malloc error\n");
    return str;
}

int test()
{
    return 1;
}
