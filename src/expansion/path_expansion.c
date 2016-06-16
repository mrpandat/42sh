#define _GNU_SOURCE

#include <util.h>
#include "../includes/expansion.h"

char *expand_path(char *path)
{
    DIR *current_dir = opendir(".");
    struct dirent *ep;
    char* res = strdup("");
    int count_match = 0;
    if (current_dir != NULL && path != NULL)
    {
        while ((ep = readdir(current_dir)) != NULL)
        {
            if (!fnmatch(path, (ep->d_name), 0))
            {
                res = str_append_free(res, ep->d_name);
                res = str_append(res, " ");
                count_match++;
            }
        }
        closedir(current_dir);
    }
    if (count_match == 0)
    {
        free(res);
        return NULL;
    }
    return res;
}

char *expand_tilde(char *word)
{
    if (!strcmp("~", word))
        return strdup(g_env.HOME);
    else if (!strcmp("~/", word))
        return str_append_char(strdup(g_env.HOME), '/');
    else if (!strcmp("~-", word))
        return strdup(g_env.OLDPWD);
    else if (!strcmp("~+", word))
        return strdup(g_env.PWD);
    return NULL;
}
