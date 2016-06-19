#include "../includes/ast.h"
#include "../includes/parser.h"

bool read_rule_while(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_WHILE)
    {
        lexer_read(l);
        node->type = ND_WHILE;
        node->data.s_while_node = init_while_node();
        return read_compound_list(node->data.s_while_node->predicate, l)
               && read_do_group(node->data.s_while_node->statement, l);
    }
    else
        return false;
}

bool read_rule_until(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_UNTIL)
    {
        lexer_read(l);
        node->type = ND_UNTIL;
        node->data.s_until_node = init_until_node();
        return read_compound_list(node->data.s_until_node->predicate, l)
               && read_do_group(node->data.s_until_node->statement, l);
    }
    else
        return false;
}

bool read_do_group(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type != TK_DO)
        return false;
    lexer_read(l);
    if (!read_compound_list(node, l))
        return false;
    if (lexer_peek(l)->type != TK_DONE)
        return false;
    lexer_read(l);
    return true;
}

static bool read_for_words(struct s_for_node *for_node, struct s_lexer *l)
{
    lexer_read(l);
    while (is_word(lexer_peek(l)))
    {
        struct s_word *word = init_word(is_word(lexer_peek(l)),
                                        lexer_peek(l)->value);
        add_for_word(for_node, word);
        lexer_read(l);
    }
    if (lexer_peek(l)->type != TK_SEMI
        && lexer_peek(l)->type != TK_NEWLINE)
        return false;
    lexer_read(l);
    read_newlines(l);
    return true;
}

bool read_rule_for(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_FOR)
    {
        lexer_read(l);
        if (!is_word(lexer_peek(l)))
            return false;
        node->type = ND_FOR;
        struct s_for_node *for_node = init_for_node(lexer_peek(l)->value);
        node->data.s_for_node = for_node;
        lexer_read(l);
        read_newlines(l);
        if (lexer_peek(l)->type == TK_IN)
        {
            if (!read_for_words(for_node, l))
                return false;
        }
        if (!read_do_group(for_node->do_group, l))
            return false;
        return true;
    }
    return false;
}
