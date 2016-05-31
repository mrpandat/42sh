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

bool read_rule_for(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_FOR && lexer_read(l)->type == TK_WORD)
    {
        node->type = ND_FOR;
        struct s_for_node *for_node = init_for_node(lexer_peek(l)->value);
        node->data.s_for_node = for_node;
        lexer_read(l);
        read_newlines(l);
        if (lexer_peek(l)->type == TK_IN)
        {
            lexer_read(l);
            while (lexer_peek(l)->type == TK_WORD)
            {
                add_for_word(for_node, lexer_peek(l)->value);
                lexer_read(l);
            }
            if (lexer_peek(l)->type != TK_SEMI
                && lexer_peek(l)->type != TK_NEWLINE)
                return false;
            lexer_read(l);
            read_newlines(l);
        }
        if (!read_do_group(for_node->do_group, l))
            return false;
        return true;
    }
    return false;
}
