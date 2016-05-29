/**
** @file execute.h
** @brief Functions related to the execution part
** @author Moisan L, Lees M
*/


#ifndef INC_42SH_EXECUTE_H
# define INC_42SH_EXECUTE_H

# include "argument_parser.h"
#include "../includes/global.h"
#include "../includes/lexer.h"
#include "ast.h"

/**
 ** @fn int execute(struct options opt)
 ** @brief Executes the command with the parameter given in the option struct
 ** @param the option structure corresponding to the command
 ** @return the result code
 */
int execute(struct options opt, struct s_ast_node *root, struct s_lexer *lexer);

/**
 ** @fn int file_test(char *name);
 ** @brief tests if a file exists and if it's executable
 ** @param path to the file
 ** @return 0 if it's ok, 127 if it does not exists, 126 if it's not executable
 */
int file_test(char *name);

#endif //INC_42SH_EXECUTE_H
