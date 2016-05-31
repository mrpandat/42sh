#include "../includes/ast.h"
#include "../includes/parser.h"

void read_newlines(struct s_lexer *lexer)
{
    while (lexer_peek(lexer)->type == TK_NEWLINE)
        lexer_read(lexer);
}

struct s_ast_node *parser(struct s_lexer *lexer)
{
    struct s_ast_node *root = init_ast_node();
    if (!read_input(root, lexer))
    {
        free_ast_node(root);
        lexer_destroy(lexer);
        return NULL;
    }
    return root;
}

bool read_redirection(struct s_redirection_node *redirection, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_IONUMBER)
    {
        redirection->io_number = lexer_peek(l)->value;
        lexer_read(l);
    }
    else
        redirection->io_number = NULL;
    if (lexer_peek(l)->type != TK_GREAT && lexer_peek(l)->type != TK_LESS
        && lexer_peek(l)->type != TK_DGREAT && lexer_peek(l)->type != TK_DLESS
        && lexer_peek(l)->type != TK_DLESSDASH
        && lexer_peek(l)->type != TK_GREATAND
        && lexer_peek(l)->type != TK_LESSAND
        && lexer_peek(l)->type != TK_CLOBBER
        && lexer_peek(l)->type != TK_LESSGREAT)
        return false;
    redirection->type = lexer_peek(l)->value;
    lexer_read(l);
    if (lexer_peek(l)->type != TK_HEREDOC && lexer_peek(l)->type != TK_WORD)
        return false;
    redirection->word = lexer_peek(l)->value;
    lexer_read(l);
    return true;
}

bool read_input(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_NEWLINE || lexer_peek(l)->type == TK_EOF)
        return true;
    else if (read_list(node, l))
        return (lexer_peek(l)->type == TK_NEWLINE
                || lexer_peek(l)->type == TK_EOF);
    else
        return false;
}
