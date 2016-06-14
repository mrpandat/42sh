#define _GNU_SOURCE

#include <util.h>
#include <hashtable.h>

#include "variables.h"

void *get_var(char *name)
{
    struct s_element *a = ht_get(g_env.variables, name);
    return a->value;
}

void set_var(char *var, void *value)
{
    ht_insert(g_env.variables, var, value);
}

int exit_var(int vcount, int values, int save, char *var, char *value)
{
    if (vcount == 0 || values == 0) return 1;
    if (save == 1) set_var(var, value);
    return 0;
}

int is_var(char *word, int save)
{
    int values = 0, vcount = 0;
    char *tmp, *var = strdup(""), *value = strdup("");
    for (size_t i = 0; i < strlen(word); i++)
    {
        if (word[i] == '\0') break;
        if (word[i] == '=')
        {
            tmp = "";
            vcount++;
            continue;
        }
        if (vcount == 0)
        {
            tmp = str_append_char(var, word[i]);
            free(var);
            var = tmp;
        }
        else
        {
            tmp = str_append_char(value, word[i]);
            free(value);
            value = tmp;
            values++;
        }
    }
    return exit_var(vcount, values, save, var, value);
}

