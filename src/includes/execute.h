/**
** @file execute.h
** @brief Functions related to the execution part
** @author Moisan L, Lees M
*/


#ifndef INC_42SH_EXECUTE_H
# define INC_42SH_EXECUTE_H

# include "argument_parser.h"
#include "global.h"
#include "lexer.h"
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

int exec_ast_node(struct s_ast_node* node);
int exec_if_node(struct s_if_node *node);
int exec_while_node(struct s_while_node *node);
int exec_until_node(struct s_until_node *node);
int exec_case_node(struct s_case_node *node);
int exec_case_item_node(struct s_case_item_node *node);
int exec_for_node(struct s_for_node *node);
int exec_redirection_node(struct s_redirection_node *node);
int exec_funcdec_node(struct s_funcdec_node *node);
int exec_simple_command_node(struct s_simple_command_node *node);
int exec_command_node(struct s_command_node *node);
int exec_pipeline_node(struct s_pipeline_node *node);
int exec_and_or_node(struct s_and_or_node *node);
int exec_list_node(struct s_list_node *node);

#endif //INC_42SH_EXECUTE_H
