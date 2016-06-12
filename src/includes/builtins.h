/**
 ** @file builtin.h
 ** @brief Builtins of 42sh
 ** @author Treibert Jean
 */


#ifndef INC_42SH_EXIT_H
#define INC_42SH_EXIT_H

# include <global.h>
# include <ast.h>

/**
 ** @fn my_exit(struct s_simple_command_node *node)
 ** @brief exists the program while freeing the ressources
 ** @param the node containing the command and the exit code
 ** @return 1 if there was an error
 */
int my_exit(struct s_simple_command_node *node);


/**
 ** @fn my_echo(struct s_simple_command_node *node)
 ** @brief prints a string on stdout folowing the sdl specifications
 ** @param the node containing the command and its arguments
 ** @return 1 if there was an error, 0 otherwise
 */

int my_echo(struct s_simple_command_node *node);

/**
 ** @fn my_cd(struct s_simple_command_node *node)
 ** @brief changes the current directory
 ** @param the node containing the command and it's arguments
 ** @return 1 if there was an error, 0 otherwise
 */
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

/**
 ** @fn my_source(struct s_simple_command_node *node)
 ** @brief executes the given script
 ** @param the node containing the command and its arguments
 ** @return 1 if there was an error, 0 otherwise
 */

int my_source(struct s_simple_command_node *node);

#endif //INC_42SH_EXIT_H
