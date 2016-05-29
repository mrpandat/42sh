/**
 ** @file parser.h
 ** @brief Functions related to the parser part
 ** @author Moisan L
 */

#ifndef PARSER_H
# define PARSER_H

# include "../includes/ast.h"
# include "../includes/lexer.h"
# include "../includes/global.h"

/**
 ** @fn struct s_ast_node *parser(struct s_lexer *lexer)
 ** @brief Construct an AST tree using tokens from the lexer
 ** @param the lexer that handle the input commands
 ** @return the root of the AST tree, or NULL if the grammar was bad
 */
struct s_ast_node *parser(struct s_lexer *lexer);

/**
 ** @fn bool read_input(struct s_ast_node *node, struct s_lexer *l)
 ** @brief Read commands and construct an AST tree
 ** @param the root node
 ** @param the lexer that handle the tokens
 ** @return true if the grammar was good, false if it was bad
 */
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
