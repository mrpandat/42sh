#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "../includes/global.h"
#include "../includes/expansion.h"
#include "../includes/util.h"
#include <fnmatch.h>

#define _GNU_SOURCE


char *expand_path(char *path)
{
    DIR *dp = opendir("./");
    struct dirent *ep;
    if (dp != NULL)
    {
        while ((ep = readdir(dp)) != NULL){
            puts(ep->d_name);
            puts("begin");
            if (!fnmatch(path, (ep->d_name), 0))
            {
                puts("ok\n");
                puts(ep->d_name);
            }
            puts("begin");

            (void) closedir(dp);
        }
    }
    else
        perror("Couldn't open the directory");
    puts("done");
    return "lol";
}
