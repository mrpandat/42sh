#include "../includes/global.h"

char *args_from_str(char *str, char ***arguments)
{
    char *prog = NULL;
    prog = strtok(str, " ");
    char *prog_name = malloc(sizeof (char) * strlen(prog) + 1);
    strcpy(prog_name, prog);
    int i = 0;
    char *arg = prog;

    while (arg != NULL)
    {
        *arguments = realloc(*arguments, sizeof (char *) * ++i);
        (*arguments)[i - 1] = arg;
        arg = strtok(NULL, " ");
    }
    *arguments = realloc(*arguments, sizeof (char *) * (i + 1));
    (*arguments)[i] = NULL;
    return prog_name;
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


char *path_to_str(char *file)
{
    FILE *f = fopen(file, "r");
    char *str = NULL;
    if (f)
    {
        fseek(f, 0, SEEK_END);
        int length = ftell(f);
        str = calloc(sizeof (char) * length + 1, sizeof (char));
        if (str != NULL)
        {
            fseek(f, 0, SEEK_SET);
            fread(str, sizeof (char), length, f);
            fclose(f);
            return str;
        }
        fclose(f);
    }
    return NULL;
}

/**
 * Be carefull this function does not closes the FILE
 * Reason : ment to be used with stdin
 */
char *file_to_str(FILE *f)
{
    char *str = NULL;
    if (f)
    {
        fseek(f, 0, SEEK_END);
        int length = ftell(f);
        str = calloc(sizeof (char) * length + 1, sizeof (char));
        if (str != NULL)
        {
            fseek(f, 0, SEEK_SET);
            fread(str, sizeof (char), length, f);
            return str;
        }
    }
    return NULL;
}


int test()
{
    return 1;
}
