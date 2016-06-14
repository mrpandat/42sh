/*! \mainpage 42sh
 **
 ** 42sh is a shell
 **
 ** By Treibert Jean, Domingues Thomas, Lucas Moisan and Martin Lees.
 */

#ifndef INC_42SH_GLOBAL_H
# define INC_42SH_GLOBAL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <libgen.h>
# include <stdbool.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fnmatch.h>

struct env
{
    struct s_ast_node *root;
    struct s_lexer *lexer;
    struct options *opt;
    char *HOME;
    char *PWD;
    char *OLDPWD;

    // Aliases hashtable
    struct s_hashtable *aliases;

    // Variables hashtable
    struct s_hashtable *variables;

    //Shopt variables
    int ast_print;
    int dotglob;
    int expand_aliases;
    int extglob;
    int nocaseglob;
    int nullglob;
    int sourcepath;
    int xpg_echo;
};

struct env g_env;

#endif
