#include "../includes/ast.h"
#include "../includes/parser.h"

void read_newlines(struct s_lexer *lexer)
{
    while (lexer_peek(lexer)->type == TK_NEWLINE)
        lexer_read(lexer);
}

struct s_ast_node *parser(char *input)
{
    struct s_lexer *lexer = lexer_init(input);
    lexer_process(lexer);
    struct s_ast_node *root = init_ast_node();
    if (!read_input(root, lexer))
        return NULL;
    return root;
}

bool read_rule_if(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type != TK_IF)
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
    if (lexer_peek(l)->type == TK_ELIF)
    {
        if (!read_rule_if(node->data.s_if_node->false_statement, l))
            return false;
    }
    else if (lexer_peek(l)->type == TK_ELSE)
    {
        if (!read_compound_list(node->data.s_if_node->false_statement, l))
            return false;
    }
    if (lexer_peek(l)->type == TK_FI)
        return true;
    else
        return false;
}

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

bool read_rule_case(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type != TK_CASE)
        return false;
    lexer_read(l);
    if (lexer_peek(l)->type != TK_WORD)
        return false;
    node->type = ND_CASE;
    struct s_case_node *case_node = init_case_node(lexer_peek(l)->value);
    node->data.s_case_node = case_node;
    lexer_read(l);
    read_newlines(l);
    if (lexer_peek(l)->type != TK_IN)
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
    return true;
}

bool read_case_item(struct s_case_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_LPAR)
        lexer_read(l);
    if (lexer_peek(l)->type != TK_WORD)
        return false;
    lexer_read(l);
    struct s_case_item_node *item = init_case_item_node();
    add_case_item(node, item);
    add_case_item_word(item, lexer_peek(l)->value);
    while (lexer_peek(l)->type == TK_OR)
    {
        if (lexer_read(l)->type != TK_WORD)
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
    return true;
}

bool read_shell_command(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_LBRACE || lexer_peek(l)->type == TK_LPAR)
    {
        lexer_read(l);
        return (read_compound_list(node, l)
                && (lexer_peek(l)->type == TK_RBRACE
                    || lexer_peek(l)->type == TK_RPAR));
    }
    return (read_rule_for(node, l)
            || read_rule_while(node, l)
            || read_rule_until(node, l)
            || read_rule_case(node, l)
            || read_rule_if(node, l));
}

bool read_funcdec(struct s_ast_node *node, struct s_lexer *l)
{
    node->type = ND_FUNCDEC;
    if (lexer_peek(l)->type == TK_FUNCTION)
        lexer_read(l);
    if (lexer_peek(l)->type != TK_WORD)
        return false;
    lexer_read(l);
    struct s_funcdec_node *funcdec_node =
            init_funcdec_node(lexer_peek(l)->value);
    if (lexer_read(l)->type != TK_LPAR || lexer_read(l)->type != TK_RPAR)
        return false;
    lexer_read(l);
    read_newlines(l);
    return read_shell_command(funcdec_node->shell_command, l);
}

bool read_prefix(struct s_element_node *element, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_ASSIGNEMENT)
    {
        element->type = EL_ASSIGNEMENT_WORD;
        element->data.assignement_word = lexer_peek(l)->value;
        return true;
    }
    else
    {
        element->data.s_redirection_node = init_redirection_node();
        if (read_redirection(element->data.s_redirection_node, l))
            return true;
        else
        {
            free(element->data.s_redirection_node);
            return false;
        }
    }
}

bool read_element(struct s_element_node *element, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_WORD)
    {
        element->type = EL_WORD;
        element->data.word = lexer_peek(l)->value;
        lexer_read(l);
        return true;
    }
    else
    {
        element->data.s_redirection_node = init_redirection_node();
        if (read_redirection(element->data.s_redirection_node, l))
            return true;
        else
        {
            free(element->data.s_redirection_node);
            return false;
        }
    }
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
    while (read_element(element, l))
    {
        add_simple_command_element(command, element);
        element = init_element_node();
        ret = true;
    }
    return ret;
}

bool read_command(struct s_ast_node *node, struct s_lexer *l)
{
    node->type = ND_COMMAND;
    struct s_command_node *command = init_command_node();
    node->data.s_command_node = command;
    if (read_simple_command(command->content, l))
        return true;
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
    return false;
}

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
            and_or->type = ND_AND_IF;
        else
            and_or->type = ND_OR_IF;
        lexer_read(l);
        read_newlines(l);
        and_or->right = init_ast_node();
        if (!read_and_or(and_or->right, l))
        {
            free(and_or->right);
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
    if (lexer_peek(l)->type == TK_AND || lexer_peek(l)->type == TK_OR)
    {
        if (lexer_peek(l)->type == TK_AND)
            list->type = ND_AND;
        else
            list->type = ND_OR;
        list->right = init_ast_node();
        if (!read_list(list->right, l))
            free(list->right);
    }
    return true;
}

bool read_compound_list(struct s_ast_node *node, struct s_lexer *l)
{
    read_newlines(l);
    node->type = ND_LIST;
    struct s_list_node *list = init_list_node();
    if (!read_and_or(list->left, l))
        return false;
    if (lexer_peek(l)->type == TK_AND || lexer_peek(l)->type == TK_SEMI
        || lexer_peek(l)->type == TK_NEWLINE)
    {
        if (lexer_peek(l)->type == TK_AND)
            list->type = ND_AND;
        else if (lexer_peek(l)->type == TK_SEMI)
            list->type = ND_OR;
        lexer_read(l);
        read_newlines(l);
        list->right = init_ast_node();
        if (!read_compound_list(list->right, l))
            free(list->right);
    }
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
