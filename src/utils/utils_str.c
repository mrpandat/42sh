#define _GNU_SOURCE

#include <sys/stat.h>
#include "../includes/global.h"

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

/**
 *
 * Warning, this function free the variable str_one given in parameters.
 */
char *str_append_free(char *str_one, char *str_two)
{
    char *str;
    if ((str = malloc(strlen(str_one) + strlen(str_two) + 1)) != NULL
        && (str[0] = '\0') == '\0')
    {
        strcat(str, str_one);
        strcat(str, str_two);
        free(str_one);
    }
    else
        fprintf(stderr, "Malloc error\n");
    return str;
}

/**
 *
 * Warning, this function free the variable str given in parameters.
 */
char *str_append_char(char *str, char c)
{
    char *ret;
    size_t len_str = strlen(str);
    if ((ret = malloc(len_str + 2)) != NULL
        && (ret[0] = '\0') == '\0')
    {
        strcat(ret, str);
        ret[len_str] = c;
        ret[len_str + 1] = '\0';
        free(str);
    }
    else
        fprintf(stderr, "Malloc error\n");
    return ret;
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

bool pattern_matching(char *pattern, char *string)
{
    if (strcmp(pattern, string) == 0)
        return true;
    else
        return false;
}



