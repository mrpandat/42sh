#define _GNU_SOURCE

#include <util.h>

#include "variables.h"

int is_var(char *word)
{
    int assignement = 0;
    char *tmp, *var = strdup(""), *assign = strdup("");
    for (size_t i = 0; i < strlen(word); i++)
    {
        if (word[i] == '\0') break;
        if (word[i]== '=')
        {
            tmp ="";
            assignement++;
            continue;
        }
        if (assignement == 0)
        {
            tmp = str_append_char(var, word[i]);
            free(var);
            var = tmp;
        }
        else {
            tmp = str_append_char(assign, word[i]);
            free(assign);
            assign = tmp;
        }
    }
    puts(var);
    puts(assign);
    return 0;
}
