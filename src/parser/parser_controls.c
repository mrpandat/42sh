#include "../includes/ast.h"
#include "../includes/parser.h"

static bool read_rule_else(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_ELIF)
    {
        node->data.s_if_node->false_statement = init_ast_node();
        if (!read_rule_if(node->data.s_if_node->false_statement, l, true))
            return false;
    }
    else if (lexer_peek(l)->type == TK_ELSE)
    {
        lexer_read(l);
        node->data.s_if_node->false_statement = init_ast_node();
        if (!read_compound_list(node->data.s_if_node->false_statement, l))
            return false;
    }
    return true;
}

bool read_rule_if(struct s_ast_node *node, struct s_lexer *l, bool elif)
{
    if (!elif && lexer_peek(l)->type != TK_IF)
        return false;
    if (elif && lexer_peek(l)->type != TK_ELIF)
        return false;
    lexer_read(l);
    node->type = ND_IF;
    node->data.s_if_node = init_if_node();
    if (!read_compound_list(node->data.s_if_node->predicate, l))
        return false;
    if (lexer_peek(l)->type != TK_THEN)
        return false;
    lexer_read(l);
    if (!read_compound_list(node->data.s_if_node->true_statement, l))
        return false;
    if (!read_rule_else(node, l))
        return false;
    if (!elif && lexer_peek(l)->type != TK_FI)
        return false;
    if (!elif)
        lexer_read(l);
    return true;
}

bool read_rule_case(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type != TK_CASE || is_word(lexer_read(l)) == WD_NONE)
        return false;
    node->type = ND_CASE;
    struct s_case_node *case_node = init_case_node(lexer_peek(l)->value);
    node->data.s_case_node = case_node;
    read_newlines(l);
    if (lexer_read(l)->type != TK_IN)
        return false;
    lexer_read(l);
    read_newlines(l);
    if (read_case_item(case_node, l))
    {
        while (lexer_peek(l)->type == TK_DSEMI)
        {
            lexer_read(l);
            read_newlines(l);
            read_case_item(case_node, l);
        }
        read_newlines(l);
    }
    if (lexer_peek(l)->type != TK_ESAC)
        return false;
    lexer_read(l);
    return true;
}

bool read_case_item(struct s_case_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_LPAR)
        lexer_read(l);
    if (is_word(lexer_peek(l)) == WD_NONE || lexer_peek(l)->type == TK_ESAC)
        return false;
    struct s_case_item_node *item = init_case_item_node();
    add_case_item(node, item);
    add_case_item_word(item, lexer_peek(l)->value);
    lexer_read(l);
    while (lexer_peek(l)->type == TK_OR)
    {
        lexer_read(l);
        if (is_word(lexer_peek(l)) == WD_NONE)
            return false;
        add_case_item_word(item, lexer_peek(l)->value);
        lexer_read(l);
    }
    if (lexer_peek(l)->type != TK_RPAR)
        return false;
    lexer_read(l);
    read_newlines(l);
    read_compound_list(item->statement, l);
    return true;
}
