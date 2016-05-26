#ifndef PARSER_H
# define PARSER_H

# include "../includes/ast.h"
# include "../includes/lexer.h"
# include "../includes/global.h"

struct s_ast_node *parser(char *command);
bool read_input(struct s_ast_node *node, struct s_lexer *l);
bool read_list(struct s_ast_node *node, struct s_lexer *l);
bool read_and_or(struct s_ast_node *node, struct s_lexer *l);
bool read_pipeline(struct s_ast_node *node, struct s_lexer *l);
bool read_command(struct s_ast_node *node, struct s_lexer *l);
bool read_simple_command(struct s_ast_node *node, struct s_lexer *l);
bool read_prefix(struct s_element_node *element, struct s_lexer *l);
bool read_element(struct s_element_node *element, struct s_lexer *l);
bool read_shell_command(struct s_ast_node *node, struct s_lexer *l);
bool read_funcdec(struct s_ast_node *node, struct s_lexer *l);
bool read_redirection(struct s_redirection_node *redirection,
                      struct s_lexer *l);
bool read_compound_list(struct s_ast_node *node, struct s_lexer *l);
bool read_rule_for(struct s_ast_node *node, struct s_lexer *l);
bool read_rule_while(struct s_ast_node *node, struct s_lexer *l);
bool read_rule_until(struct s_ast_node *node, struct s_lexer *l);
bool read_rule_case(struct s_ast_node *node, struct s_lexer *l);
bool read_rule_if(struct s_ast_node *node, struct s_lexer *l);
bool read_do_group(struct s_ast_node *node, struct s_lexer *l);
bool read_case_item(struct s_case_node *node, struct s_lexer *l);

#endif //PARSER_H
