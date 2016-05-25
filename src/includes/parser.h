#ifndef PARSER_H
# define PARSER_H

# include "ast.h"
#include <stdbool.h>

void parser(void);
bool read_input(struct s_ast_node* node);
bool read_list(struct s_ast_node* node);
bool read_and_or(struct s_ast_node* node);
bool read_pipeline(struct s_ast_node* node);
bool read_command(struct s_ast_node* node);
bool read_simple_command(struct s_ast_node* node);
bool read_prefix(struct s_element_node *element);
bool read_element(struct s_element_node *element);
bool read_shell_command(struct s_ast_node* node);
bool read_funcdec(struct s_ast_node* node);
bool read_redirection(struct s_ast_node* node);
bool read_compound_list(struct s_ast_node* node);
bool read_rule_for(struct s_ast_node* node);
bool read_rule_while(struct s_ast_node* node);
bool read_rule_until(struct s_ast_node *node);
bool read_rule_case(struct s_ast_node *node);
bool read_rule_if(struct s_ast_node* node);
bool read_do_group(struct s_ast_node* node);
bool read_case_item(struct s_ast_node *node);

#endif //PARSER_H