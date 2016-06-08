#include <builtins.h>

int set_option(char *option, int opt)
{
    if(!strcmp(option, "ast_print")) {
        g_env.ast_print = opt;
    } else if(!strcmp(option, "dotglob")) {
        g_env.dotglob = opt;
    }  else if(!strcmp(option, "expand_aliases")) {
        g_env.expand_aliases = opt;
    }  else if(!strcmp(option, "extglob")) {
        g_env.extglob = opt;
    }  else if(!strcmp(option, "nocaseglob")) {
        g_env.nocaseglob = opt;
    }  else if(!strcmp(option, "nullglob")) {
        g_env.nullglob = opt;
    }  else if(!strcmp(option, "sourcepath")) {
        g_env.sourcepath = opt;
    }  else if(!strcmp(option, "xpg_echo")) {
        g_env.xpg_echo= opt;
    }
    else
    {
        fprintf(stderr, "42sh: %s :  invalid shell option name\n", option);
        exit(2);
    }
    return 1;
}

