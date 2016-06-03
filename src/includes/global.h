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
};

struct env g_env;

#endif
