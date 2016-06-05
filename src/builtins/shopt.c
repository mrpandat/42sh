#include <builtins.h>

int set_option(char *option, int opt)
{
    if(strcmp(option, "astprint")) {
        g_env.ast_print = 0;
    } else if(strcmp(option, "dotglob")) {
        g_env.dotglob = 0;
    }  else if(strcmp(option, "expand_aliases")) {
        g_env.expand_aliases = 0;
    }  else if(strcmp(option, "extglob")) {
        g_env.extglob = 0;
    }  else if(strcmp(option, "nocaseglob")) {
        g_env.nocaseglob = 0;
    }  else if(strcmp(option, "nullglob")) {
        g_env.nullglob = 0;
    }  else if(strcmp(option, "sourcepath")) {
        g_env.sourcepath = 0;
    }  else if(strcmp(option, "xpg_echo")) {
        g_env.xpg_echo= 0;
    }
    return 1;
}

