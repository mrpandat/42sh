#include "../includes/ast.h"
#include "../includes/parser.h"

bool read_prefix(struct s_element_node *element, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_ASSIGNEMENT)
    {
        element->type = EL_WORD;
        element->data.s_word = malloc(sizeof (struct s_word));
        element->data.s_word->value = lexer_peek(l)->value;
        return true;
    }
    else
    {
        element->type = EL_REDIRECTION;
        element->data.s_redirection_node = init_redirection_node();
        if (read_redirection(element->data.s_redirection_node, l))
            return true;
        else
        {
            element->type = EL_NONE;
            free_redirection_node(element->data.s_redirection_node);
            return false;
        }
    }
}

bool read_element(struct s_element_node *element, struct s_lexer *l)
{
    enum e_word_type tk_type = is_word(lexer_peek(l));
    if (tk_type != WD_NONE)
    {
        element->type = EL_WORD;
        element->data.s_word = malloc(sizeof (struct s_word));
        element->data.s_word->value = lexer_peek(l)->value;
        lexer_read(l);
        return true;
    }
    else
    {
        element->type = EL_REDIRECTION;
        element->data.s_redirection_node = init_redirection_node();
        if (read_redirection(element->data.s_redirection_node, l))
            return true;
        else
        {
            element->type = EL_NONE;
            free_redirection_node(element->data.s_redirection_node);
            return false;
        }
    }
}
