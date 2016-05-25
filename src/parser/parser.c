#include <ast.h>
#include "../includes/global.h"
#include "../includes/parser.h"
#include "../includes/ast.h"
#include "../includes/lexer.h"

void parser()
{
    printf("working parser \n");
}

bool read_rule_if(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type != TK_IF)
        return false;
    node->type = ND_IF;
    node->data.s_if_node = malloc(sizeof(struct s_if_node));
    node->data.s_if_node->false_statement = init_ast_node();
    node->data.s_if_node->predicate = init_ast_node();
    node->data.s_if_node->true_statement = init_ast_node();
    if (!read_compound_list(node->data.s_if_node->predicate, NULL)
        && lexer_peek(l)->type != TK_THEN
        && !read_compound_list(node->data.s_if_node->true_statement, l))
        return false;
    if (lexer_peek(l)->type == TK_ELIF)
        return read_rule_if(node->data.s_if_node->false_statement, l);
    else if (lexer_peek(l)->type == TK_ELSE)
        return read_compound_list(node->data.s_if_node->false_statement, l);
    else
        return true;
}

bool read_rule_while(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_WHILE)
    {
        node->type = ND_WHILE;
        node->data.s_while_node = malloc(sizeof(struct s_while_node));
        node->data.s_while_node->predicate = init_ast_node();
        node->data.s_while_node->statement = init_ast_node();
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
        node->type = ND_UNTIL;
        node->data.s_while_node = malloc(sizeof(struct s_while_node));
        node->data.s_while_node->predicate = init_ast_node();
        node->data.s_while_node->statement = init_ast_node();
        return read_compound_list(node->data.s_until_node->predicate, l)
               && read_do_group(node->data.s_until_node->statement, l);
    }
    else
        return false;
}

bool read_do_group(struct s_ast_node *node, struct s_lexer *l)
{
    return (lexer_peek(l)->type == TK_DO
            && read_compound_list(node, l)
            && lexer_peek(l)->type == TK_DONE);
}

bool read_rule_case(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_CASE && lexer_read(l)->type == TK_WORD)
    {
        node->type = ND_CASE;
        node->data.s_case_node = malloc(sizeof(struct s_case_node));
        node->data.s_case_node->word = lexer_peek(l)->value;
        node->data.s_case_node->nb_items = 0;
        node->data.s_case_node->items = NULL;
        while (lexer_read(l)->type == TK_NEWLINE)
            continue;
        if (read_case_item(node, l))
        {
            while (lexer_peek(l)->type == TK_DSEMI)
            {
                while (lexer_read(l)->type == TK_NEWLINE)
                    continue;
                read_case_item(node, l);
            }
            while (lexer_read(l)->type == TK_NEWLINE)
                continue;
        }
        if (lexer_peek(l)->type != TK_ESAC)
            return false;
        return true;
    }
    else
        return false;
}

bool read_case_item(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_LPAR && lexer_read(l)->type == TK_WORD
        && node->type == ND_CASE)
    {
        struct s_case_node *case_node = node->data.s_case_node;
        case_node->nb_items++;
        case_node->items = realloc(case_node->items,
                                   case_node->nb_items
                                   * sizeof(struct s_ast_node *));
        case_node->items[case_node->nb_items] = init_ast_node();
        struct s_case_item_node *item = malloc(sizeof(struct s_case_item_node));
        case_node->items[case_node->nb_items]->type = ND_CASE_ITEM;
        case_node->items[case_node->nb_items]->data.s_case_item_node = item;
        item->nb_words = 1;
        item->words = malloc(sizeof(struct s_ast_node *));
        item->words[0] = lexer_peek(l)->value;
        item->statement = init_ast_node();
        while (lexer_read(l)->type == TK_OR && lexer_read(l)->type == TK_WORD)
        {
            item->nb_words++;
            item->words = realloc(item->words,
                                  item->nb_words * sizeof(struct s_ast_node *));
            item->words[item->nb_words - 1] = lexer_peek(l)->value;
        }
        while (lexer_read(l)->type == TK_NEWLINE)
            continue;
        read_compound_list(item->statement, l);
        return true;
    }
    return false;
}

bool read_rule_for(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_FOR && lexer_read(l)->type == TK_WORD)
    {
        node->type = ND_FOR;
        struct s_for_node *for_node = malloc(sizeof(struct s_for_node));
        node->data.s_for_node = for_node;
        for_node->iterator = lexer_peek(l)->value;
        for_node->nb_words = 0;
        for_node->do_group = init_ast_node();
        while (lexer_read(l)->type == TK_NEWLINE)
            continue;
        if (lexer_read(l)->type == TK_IN)
        {
            while (lexer_read(l)->type == TK_WORD)
            {
                for_node->nb_words++;
                for_node->words = realloc(for_node->words,
                                          for_node->nb_words * sizeof(char *));
                for_node->words[for_node->nb_words - 1] = lexer_peek(l)->value;
            }
            lexer_read(l);
            if (lexer_peek(l)->type != TK_SEMI &&
                lexer_peek(l)->type != TK_NEWLINE)
                return false;
            while (lexer_read(l)->type == TK_NEWLINE)
                continue;
        }
        if (!read_do_group(for_node->do_group, l))
            return false;
        return true;
    }
    return false;
}

bool read_redirection(struct s_ast_node *node, struct s_lexer *l)
{
    node->type = ND_REDIRECTION;
    node->data.s_redirection_node = malloc(sizeof(struct s_redirection_node *));
    if (lexer_peek(l)->type != TK_IONUMBER)
        node->data.s_redirection_node->io_number = NULL;
    else
    {
        node->data.s_redirection_node->io_number = lexer_peek(l)->value;
        lexer_read(l);
    }
    if (lexer_peek(l)->type != TK_GREAT && lexer_peek(l)->type != TK_LESS &&
        lexer_peek(l)->type != TK_DGREAT
        && lexer_peek(l)->type != TK_DLESS &&
        lexer_peek(l)->type != TK_DLESSDASH && lexer_peek(l)->type != TK_GREATAND
        && lexer_peek(l)->type != TK_LESSAND &&
        lexer_peek(l)->type != TK_CLOBBER && lexer_peek(l)->type != TK_LESSGREAT)
        return false;
    node->data.s_redirection_node->type = lexer_peek(l)->value;
    lexer_read(l);
    if (lexer_peek(l)->type != TK_HEREDOC && lexer_peek(l)->type != TK_WORD)
        return false;
    node->data.s_redirection_node->word = lexer_peek(l)->value;
    return true;
}

bool read_shell_command(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_LBRACE || lexer_peek(l)->type == TK_LPAR)
        return (read_compound_list(node, l) && (lexer_peek(l)->type == TK_RBRACE ||
                                             lexer_peek(l)->type == TK_RPAR));
    return (read_rule_for(node, l)
            || read_rule_while(node, l)
            || read_rule_until(node, l)
            || read_rule_case(node, l)
            || read_rule_if(node, l));
}

bool read_funcdec(struct s_ast_node *node, struct s_lexer *l)
{
    node->type = ND_FUNCDEC;
    node->data.s_funcdec_node = malloc(sizeof(struct s_funcdec_node *));
    node->data.s_funcdec_node->name = NULL;
    node->data.s_funcdec_node->shell_command = init_ast_node();
    if (lexer_peek(l)->type == TK_FUNCTION)
        lexer_read(l);
    if (lexer_peek(l)->type != TK_WORD)
        return false;
    node->data.s_funcdec_node->name = lexer_peek(l)->value;
    if (lexer_read(l)->type != TK_LPAR || lexer_read(l)->type != TK_RPAR)
        return false;
    while (lexer_read(l)->type == TK_NEWLINE)
        continue;
    return read_shell_command(node->data.s_funcdec_node->shell_command, l);
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
        element->data.s_redirection_node = init_ast_node();
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
        return true;
    }
    else
    {
        element->data.s_redirection_node = init_ast_node();
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
    struct s_simple_command_node *command = malloc(
            sizeof(struct s_simple_command_node *));
    node->data.s_simple_command_node = command;
    command->nb_elements = 0;
    struct s_element_node *element = malloc(sizeof(struct s_element_node));
    while (read_prefix(element, l))
    {
        element = malloc(sizeof(struct s_element_node));
        ret = true;
    }
    while (read_element(element, l))
    {
        element = malloc(sizeof(struct s_element_node));
        ret = true;
    }
    return ret;
}

bool read_command(struct s_ast_node *node, struct s_lexer *l)
{
    node->type = ND_COMMAND;
    struct s_command_node *command = malloc(sizeof(struct s_command_node *));
    node->data.s_command_node = command;
    command->nb_redirections = 0;
    command->redirections = NULL;
    command->content = init_ast_node();
    if (read_simple_command(command->content, l))
        return true;
    if (read_shell_command(command->content, l) ||
            read_funcdec(command->content, l))
    {
        struct s_ast_node *redirection = init_ast_node();
        while (read_redirection(redirection, l))
        {
            command->nb_redirections++;
            command->redirections = realloc(command->redirections,
                                            command->nb_redirections *
                                            sizeof(struct s_ast_node *));
            command->redirections[command->nb_redirections - 1] = redirection;
            redirection = init_ast_node();
        }
        free(redirection);
        return true;
    }
    return false;
}

bool read_pipeline(struct s_ast_node *node, struct s_lexer *l)
{
    node->type = ND_PIPELINE;
    struct s_pipeline_node *pipeline = malloc(sizeof(struct s_pipeline_node));
    node->data.s_pipeline_node = pipeline;
    pipeline->nb_commands = 1;
    pipeline->commands = malloc(
            pipeline->nb_commands * sizeof(struct s_ast_node *));
    if ((pipeline->banged = (lexer_peek(l)->type == TK_BANG)))
        lexer_read(l);
    if (!read_compound_list(pipeline->commands[0], l))
        return false;
    while (lexer_peek(l)->type == TK_OR)
    {
        while (lexer_read(l)->type == TK_NEWLINE)
            continue;
        pipeline->nb_commands++;
        pipeline->commands = realloc(pipeline->commands, pipeline->nb_commands *
                                                         sizeof(struct s_ast_node *));
        if (!read_compound_list(pipeline->commands[0], l))
        {
            return false;
        }
    }
    return true;
}

bool read_and_or(struct s_ast_node *node, struct s_lexer *l)
{
    node->type = ND_AND_OR;
    struct s_and_or_node *and_or = malloc(sizeof(struct s_and_or_node));
    node->data.s_and_or_node = and_or;
    and_or->left = init_ast_node();
    and_or->type = ND_IF_NONE;
    and_or->right = NULL;
    if (!read_pipeline(and_or->left, l))
        return false;
    if (lexer_peek(l)->type == TK_AND_IF || lexer_peek(l)->type == TK_OR_IF)
    {
        if (lexer_peek(l)->type == TK_AND_IF)
            and_or->type = ND_AND_IF;
        else
            and_or->type = ND_OR_IF;
        while (lexer_read(l)->type == TK_NEWLINE)
            continue;
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
    struct s_list_node *list = malloc(sizeof(struct s_list_node));
    list->left = init_ast_node();
    list->type = ND_LIST_NONE;
    list->right = NULL;
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
    while (lexer_peek(l)->type == TK_NEWLINE)
        lexer_read(l);
    node->type = ND_LIST;
    struct s_list_node *list = malloc(sizeof(struct s_list_node));
    list->left = init_ast_node();
    list->type = ND_LIST_NONE;
    list->right = NULL;
    if (!read_and_or(list->left, l))
        return false;
    if (lexer_peek(l)->type == TK_AND || lexer_peek(l)->type == TK_OR
        || lexer_peek(l)->type == TK_NEWLINE)
    {
        if (lexer_peek(l)->type == TK_AND)
            list->type = ND_AND;
        else
            list->type = ND_OR;
        while(lexer_read(l)->type == TK_NEWLINE)
            continue;
        list->right = init_ast_node();
        if (!read_compound_list(list->right, l))
            free(list->right);
    }
}

bool read_input(struct s_ast_node *node, struct s_lexer *l)
{
    if (lexer_peek(l)->type == TK_NEWLINE || lexer_peek(l)->type == TK_EOF)
        return true;
    else if (read_list(node, l))
        return (lexer_peek(l)->type == TK_NEWLINE ||
                lexer_peek(l)->type == TK_EOF);
    else
        return false;
}
