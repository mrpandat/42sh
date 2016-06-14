#define _GNU_SOURCE

#include <dirent.h>
#include <util.h>
#include "../includes/expansion.h"

char *expand_path(char *path)
{
    DIR *current_dir = opendir(".");
    struct dirent *ep;
    char* res = strdup("");
    char* tmp;
    int count_match = 0;
    if (current_dir != NULL && path != NULL)
    {
        while ((ep = readdir(current_dir)) != NULL)
        {
            if (!fnmatch(path, (ep->d_name), 0))
            {
                tmp = str_append(res, ep->d_name);
                free(res);
                res = tmp;
                tmp = str_append(tmp, " ");
                free(res);
                res = tmp;
                count_match++;
            }
        }
        closedir(current_dir);
    }
    puts(res);
    if(count_match==0)
    {
        free(res);
        return NULL;
    }
    return res;
}
