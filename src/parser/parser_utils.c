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
    if (lexer_peek(l)->type != TK_HEREDOC && !is_word(lexer_peek(l)))
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

enum e_word_type is_word(struct s_lexer_token *token)
{
    if (token == NULL)
        return WD_NONE;
    enum e_token_type word_types[] =
    {
        TK_WORD, TK_ESC_WORD, TK_IF, TK_THEN, TK_ELSE, TK_ELIF, TK_FI, TK_DO,
        TK_DONE, TK_CASE, TK_ESAC, TK_WHILE, TK_UNTIL, TK_FOR, TK_IN,
        TK_FUNCTION, TK_IONUMBER, TK_VARIABLE
    };
    for (int i = 0; i < 18; i++)
    {
        if (token->type == word_types[i])
        {
            if (token->type == TK_ESC_WORD)
                return WD_ESC;
            else if (token->type == TK_ARITH)
                return WD_ARITH;
            else if  (token->type == TK_SUBSHELL)
                return WD_SUBSHELL;
            else if (token->type == TK_VARIABLE)
                return WD_VARIABLE;
            else
                return WD_WORD;
        }
    }
    return WD_NONE;
}
