#include "../includes/ast.h"
#include "../includes/parser.h"

bool read_pipeline(struct s_ast_node *node, struct s_lexer *l)
{
    node->type = ND_PIPELINE;
    struct s_pipeline_node *pipeline = init_pipeline_node();
    node->data.s_pipeline_node = pipeline;
    if ((pipeline->banged = (lexer_peek(l)->type == TK_BANG)))
        lexer_read(l);
    add_pipeline_command(pipeline, init_ast_node());
    if (!read_command(pipeline->commands[0], l))
        return false;
    while (lexer_peek(l)->type == TK_OR)
    {
        lexer_read(l);
        read_newlines(l);
        add_pipeline_command(pipeline, init_ast_node());
        if (!read_command(pipeline->commands[pipeline->nb_commands - 1], l))
            return false;
    }
    return true;
}

bool read_and_or(struct s_ast_node *node, struct s_lexer *l)
{
    node->type = ND_AND_OR;
    struct s_and_or_node *and_or = init_and_or_node();
    node->data.s_and_or_node = and_or;
    if (!read_pipeline(and_or->left, l))
        return false;
    if (lexer_peek(l)->type == TK_AND_IF || lexer_peek(l)->type == TK_OR_IF)
    {
        if (lexer_peek(l)->type == TK_AND_IF)
            and_or->type = ANDOR_AND;
        else
            and_or->type = ANDOR_OR;
        lexer_read(l);
        read_newlines(l);
        and_or->right = init_ast_node();
        if (!read_and_or(and_or->right, l))
        {
            and_or->type = ANDOR_NONE;
            return false;
        }
    }
    return true;
}

bool read_list(struct s_ast_node *node, struct s_lexer *l)
{
    node->type = ND_LIST;
    struct s_list_node *list = init_list_node();
    node->data.s_list_node = list;
    if (!read_and_or(list->left, l))
        return false;
    if (lexer_peek(l)->type == TK_AND || lexer_peek(l)->type == TK_SEMI)
    {
        if (lexer_peek(l)->type == TK_AND)
            list->type = LIST_AND;
        else
            list->type = LIST_SEMI;
        lexer_read(l);
        list->right = init_ast_node();
        if (!read_list(list->right, l) && list->type == LIST_AND)
            list->type = LIST_BG;
    }
    else if (lexer_peek(l)->type == TK_NEWLINE)
    {
        read_newlines(l);
        list->type = LIST_SEMI;
        list->right = init_ast_node();
        if (!read_list(list->right, l))
        {
            free_ast_node(list->right);
            list->type = LIST_NONE;
        }
    }
    return true;
}

bool read_compound_list(struct s_ast_node *node, struct s_lexer *l)
{
    read_newlines(l);
    node->type = ND_LIST;
    struct s_list_node *list = init_list_node();
    node->data.s_list_node = list;
    if (!read_and_or(list->left, l))
        return false;
    if (lexer_peek(l)->type == TK_AND || lexer_peek(l)->type == TK_SEMI
        || lexer_peek(l)->type == TK_NEWLINE)
    {
        if (lexer_peek(l)->type == TK_AND)
            list->type = LIST_AND;
        else
            list->type = LIST_SEMI;
        lexer_read(l);
        read_newlines(l);
        list->right = init_ast_node();
        if (!read_compound_list(list->right, l))
            list->type = LIST_BG;
    }
    return true;
}

