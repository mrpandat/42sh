#include "../includes/ast.h"
#include "../includes/parser.h"

bool read_shell_command(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_LBRACE)
    {
        lexer_read(l);
        return (read_compound_list(node, l)
                && (lexer_peek(l)->type == TK_RBRACE));
    }
    if (lexer_peek(l)->type == TK_LPAR)
    {
        lexer_read(l);
        return (read_compound_list(node, l)
                && (lexer_peek(l)->type == TK_RPAR));
    }
    return (read_rule_for(node, l)
            || read_rule_while(node, l)
            || read_rule_until(node, l)
            || read_rule_case(node, l)
            || read_rule_if(node, l, false));
}

bool read_funcdec(struct s_ast_node *node, struct s_lexer *l)
{
    node->type = ND_FUNCDEC;
    if (lexer_peek(l)->type == TK_FUNCTION)
        lexer_read(l);
    if (is_word(lexer_peek(l)) == WD_NONE || lexer_peek(l)->next == NULL
        || lexer_peek(l)->next->type != TK_LPAR
        || lexer_peek(l)->next->next == NULL
        || lexer_peek(l)->next->next->type != TK_RPAR)
        return false;
    struct s_funcdec_node *funcdec_node =
            init_funcdec_node(lexer_peek(l)->value);
    node->data.s_funcdec_node = funcdec_node;
    if (lexer_read(l)->type != TK_LPAR || lexer_read(l)->type != TK_RPAR)
        return false;
    lexer_read(l);
    read_newlines(l);
    return read_shell_command(funcdec_node->shell_command, l);
}

bool read_simple_command(struct s_ast_node *node, struct s_lexer *l)
{
    bool ret = false;
    node->type = ND_SIMPLE_COMMAND;
    struct s_simple_command_node *command = init_simple_command_node();
    node->data.s_simple_command_node = command;
    struct s_element_node *element = init_element_node();
    while (read_prefix(element, l))
    {
        add_simple_command_element(command, element);
        element = init_element_node();
        ret = true;
    }
    int el_res = 0;
    while ((el_res = read_element(element, l)) == 1)
    {
        add_simple_command_element(command, element);
        element = init_element_node();
        ret = true;
    }
    free_element_node(element);
    if (el_res < 0)
        return false;
    return ret;
}

bool read_command(struct s_ast_node *node, struct s_lexer *l)
{
    node->type = ND_COMMAND;
    struct s_command_node *command = init_command_node();
    node->data.s_command_node = command;
    if (read_shell_command(command->content, l)
        || read_funcdec(command->content, l))
    {
        struct s_redirection_node *redirection = init_redirection_node();
        while (read_redirection(redirection, l))
        {
            add_command_redirection(command, redirection);
            redirection = init_redirection_node();
        }
        free(redirection);
        return true;
    }
    if (read_simple_command(command->content, l))
        return true;
    return false;
}
