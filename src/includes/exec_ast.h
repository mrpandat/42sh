#ifndef INC_42SH_EXEC_AST_H
#define INC_42SH_EXEC_AST_H

# include "ast.h"
# include "global.h"

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

#endif //INC_42SH_EXEC_AST_H
