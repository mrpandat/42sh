/**
 ** @file builtin.h
 ** @brief Builtins of 42sh
 ** @author Treibert Jean
 */


#ifndef INC_42SH_EXIT_H
#define INC_42SH_EXIT_H

# include <global.h>
# include <ast.h>

int my_exit(struct s_simple_command_node *node);
int my_echo(struct s_simple_command_node *node);
int my_cd(struct s_simple_command_node *node);
int my_alias(struct s_simple_command_node *node);
int my_unalias(struct s_simple_command_node *node);

/**
 ** @struct echo_struct
 ** @brief The echo structure
 ** @details This structure contains the options of echo builtin.
 */

struct echo_struct
{
    int noption;
    int eoption;
    int Eoption;
    int options;
};

int set_option(char *option, int opt);

#endif //INC_42SH_EXIT_H
