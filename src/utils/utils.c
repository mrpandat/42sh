#define _GNU_SOURCE

#include <sys/stat.h>
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

int my_pow(int a, int b)
{
    int ret = 1;
    if (b == 0)
        return 1;
    else if (b > 0)
    {
        for (int i = 0; i < b; i++)
            ret = ret * a;
    }
    return ret;
}


int test()
{
    return 1;
}

int file_test(char *name)
{
    struct stat *stats = malloc(sizeof (struct stat));
    int res = 0;
    if (stat(name, stats) > -1)
    {
        if (S_ISREG(stats->st_mode))
            res = 0;
        else if (S_ISDIR(stats->st_mode))
            res = 33;
        else
            res = 127;
    }
    else
        res = 127;
    if (res == 0 && !(stats->st_mode & S_IXUSR))
        res = 126;
    free(stats);

    return res;
}

