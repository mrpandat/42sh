#include <stdio.h>
#include <dirent.h>
#include "../includes/global.h"
#include "../includes/expansion.h"


#define _GNU_SOURCE


char *expand_path(char *path)
{
    DIR *dp = opendir(".");
    struct dirent *ep;
    if (dp != NULL && path != NULL)
    {
        while ((ep = readdir(dp)) != NULL)
        {
            puts(ep->d_name);
            if (!fnmatch(path, (ep->d_name), 0))
                puts(ep->d_name);
        }
        closedir(dp);
    }
    return "lol";
}
