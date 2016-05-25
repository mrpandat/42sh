#include <ast.h>
#include "../includes/global.h"
#include "../includes/parser.h"
#include "../includes/ast.h"
#include "../includes/lexer.h"

void parser()
{
    printf("working parser \n");
}

bool read_rule_if(struct s_ast_node *node)
{
    if (lexer_peek()->type != TK_IF)
        return false;
    node->type = ND_IF;
    node->data.s_if_node = malloc(sizeof(struct s_if_node));
    node->data.s_if_node->false_statement = init_ast_node();
    node->data.s_if_node->predicate = init_ast_node();
    node->data.s_if_node->true_statement = init_ast_node();
    if (!read_compound_list(node->data.s_if_node->predicate)
        && lexer_peek()->type != TK_THEN
        && !read_compound_list(node->data.s_if_node->true_statement))
        return false;
    if (lexer_peek()->type == TK_ELIF)
        return read_rule_if(node->data.s_if_node->false_statement);
    else if (lexer_peek()->type == TK_ELSE)
        return read_compound_list(node->data.s_if_node->false_statement);
    else
        return true;
}

bool read_rule_while(struct s_ast_node *node)
{
    if (lexer_peek()->type == TK_WHILE)
    {
        node->type = ND_WHILE;
        node->data.s_while_node = malloc(sizeof(struct s_while_node));
        node->data.s_while_node->predicate = init_ast_node();
        node->data.s_while_node->statement = init_ast_node();
        return read_compound_list(node->data.s_while_node->predicate)
               && read_do_group(node->data.s_while_node->statement);
    }
    else
        return false;
}

bool read_rule_until(struct s_ast_node *node)
{
    if (lexer_peek()->type == TK_UNTIL)
    {
        node->type = ND_UNTIL;
        node->data.s_while_node = malloc(sizeof(struct s_while_node));
        node->data.s_while_node->predicate = init_ast_node();
        node->data.s_while_node->statement = init_ast_node();
        return read_compound_list(node->data.s_until_node->predicate)
               && read_do_group(node->data.s_until_node->statement);
    }
    else
        return false;
}

bool read_do_group(struct s_ast_node *node)
{
    return (lexer_peek()->type == TK_DO
            && read_compound_list(node)
            && lexer_peek()->type == TK_DONE);
}

bool read_rule_case(struct s_ast_node *node)
{
    if (lexer_peek()->type == TK_CASE && lexer_read()->type == TK_WORD)
    {
        node->type = ND_CASE;
        node->data.s_case_node = malloc(sizeof(struct s_case_node));
        node->data.s_case_node->word = lexer_peek()->value;
        node->data.s_case_node->nb_items = 0;
        node->data.s_case_node->items = NULL;
        while (lexer_read()->type == TK_NEWLINE)
            continue;
        if (read_case_item(node))
        {
            while (lexer_peek()->type == TK_DSEMI)
            {
                while (lexer_read()->type == TK_NEWLINE)
                    continue;
                read_case_item(node);
            }
            while (lexer_read()->type == TK_NEWLINE)
                continue;
        }
        if (lexer_peek()->type != TK_ESAC)
            return false;
        return true;
    }
    else
        return false;
}

bool read_case_item(struct s_ast_node *node)
{
    if (lexer_peek()->type == TK_LPAR && lexer_read()->type == TK_WORD
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
        item->words[0] = lexer_peek()->value;
        item->statement = init_ast_node();
        while (lexer_read()->type == TK_OR && lexer_read()->type == TK_WORD)
        {
            item->nb_words++;
            item->words = realloc(item->words,
                                  item->nb_words * sizeof(struct s_ast_node *));
            item->words[item->nb_words - 1] = lexer_peek()->value;
        }
        while (lexer_read()->type == TK_NEWLINE)
            continue;
        read_compound_list(item->statement);
        return true;
    }
    return false;
}

bool read_rule_for(struct s_ast_node *node)
{
    if (lexer_peek()->type == TK_FOR && lexer_read()->type == TK_WORD)
    {
        node->type = ND_FOR;
        struct s_for_node *for_node = malloc(sizeof(struct s_for_node));
        node->data.s_for_node = for_node;
        for_node->iterator = lexer_peek()->value;
        for_node->nb_words = 0;
        for_node->do_group = init_ast_node();
        while (lexer_read()->type == TK_NEWLINE)
            continue;
        if (lexer_read()->type == TK_IN)
        {
            while (lexer_read()->type == TK_WORD)
            {
                for_node->nb_words++;
                for_node->words = realloc(for_node->words,
                                          for_node->nb_words * sizeof(char *));
                for_node->words[for_node->nb_words - 1] = lexer_peek()->value;
            }
            lexer_read();
            if (lexer_peek()->type != TK_SEMI &&
                lexer_peek()->type != TK_NEWLINE)
                return false;
            while (lexer_read()->type == TK_NEWLINE)
                continue;
        }
        if (!read_do_group(for_node->do_group))
            return false;
        return true;
    }
    return false;
}

bool read_redirection(struct s_ast_node *node)
{
    node->type = ND_REDIRECTION;
    node->data.s_redirection_node = malloc(sizeof(struct s_redirection_node *));
    if (lexer_peek()->type != TK_IONUMBER)
        node->data.s_redirection_node->io_number = NULL;
    else
    {
        node->data.s_redirection_node->io_number = lexer_peek()->value;
        lexer_read();
    }
    if (lexer_peek()->type != TK_GREAT && lexer_peek()->type != TK_LESS &&
        lexer_peek()->type != TK_DGREAT
        && lexer_peek()->type != TK_DLESS &&
        lexer_peek()->type != TK_DLESSDASH && lexer_peek()->type != TK_GREATAND
        && lexer_peek()->type != TK_LESSAND &&
        lexer_peek()->type != TK_CLOBBER && lexer_peek()->type != TK_LESSGREAT)
        return false;
    node->data.s_redirection_node->type = lexer_peek()->value;
    lexer_read();
    if (lexer_peek()->type != TK_HEREDOC && lexer_peek()->type != TK_WORD)
        return false;
    node->data.s_redirection_node->word = lexer_peek()->value;
    return true;
}

bool read_shell_command(struct s_ast_node *node)
{
    if (lexer_peek()->type == TK_LBRACE || lexer_peek()->type == TK_LPAR)
        return (read_compound_list(node) && (lexer_peek()->type == TK_RBRACE ||
                                             lexer_peek()->type == TK_RPAR));
    return (read_rule_for(node)
            || read_rule_while(node)
            || read_rule_until(node)
            || read_rule_case(node)
            || read_rule_if(node));
}

bool read_funcdec(struct s_ast_node *node)
{
    node->type = ND_FUNCDEC;
    node->data.s_funcdec_node = malloc(sizeof(struct s_funcdec_node *));
    node->data.s_funcdec_node->name = NULL;
    node->data.s_funcdec_node->shell_command = init_ast_node();
    if (lexer_peek()->type == TK_FUNCTION)
        lexer_read();
    if (lexer_peek()->type != TK_WORD)
        return false;
    node->data.s_funcdec_node->name = lexer_peek()->value;
    if (lexer_read()->type != TK_LPAR || lexer_read()->type != TK_RPAR)
        return false;
    while (lexer_read()->type == TK_NEWLINE)
        continue;
    return read_shell_command(node->data.s_funcdec_node->shell_command);
}

bool read_prefix(struct s_element_node *element)
{
    if (lexer_peek()->type == TK_ASSIGNEMENT)
    {
        element->type = EL_ASSIGNEMENT_WORD;
        element->data.assignement_word = lexer_peek()->value;
        return true;
    }
    else
    {
        element->data.s_redirection_node = init_ast_node();
        if (read_redirection(element->data.s_redirection_node))
            return true;
        else
        {
            free(element->data.s_redirection_node);
            return false;
        }
    }
}

bool read_element(struct s_element_node *element)
{
    if (lexer_peek()->type == TK_WORD)
    {
        element->type = EL_WORD;
        element->data.word = lexer_peek()->value;
        return true;
    }
    else
    {
        element->data.s_redirection_node = init_ast_node();
        if (read_redirection(element->data.s_redirection_node))
            return true;
        else
        {
            free(element->data.s_redirection_node);
            return false;
        }
    }
}

bool read_simple_command(struct s_ast_node *node)
{
    bool ret = false;
    node->type = ND_SIMPLE_COMMAND;
    struct s_simple_command_node *command = malloc(
            sizeof(struct s_simple_command_node *));
    node->data.s_simple_command_node = command;
    command->nb_elements = 0;
    struct s_element_node *element = malloc(sizeof(struct s_element_node));
    while (read_prefix(element))
    {
        element = malloc(sizeof(struct s_element_node));
        ret = true;
    }
    while (read_element(element))
    {
        element = malloc(sizeof(struct s_element_node));
        ret = true;
    }
    return ret;
}

bool read_command(struct s_ast_node *node)
{
    node->type = ND_COMMAND;
    struct s_command_node *command = malloc(sizeof(struct s_command_node *));
    node->data.s_command_node = command;
    command->nb_redirections = 0;
    command->redirections = NULL;
    command->content = init_ast_node();
    if (read_simple_command(command->content))
        return true;
    if (read_shell_command(command->content) || read_funcdec(command->content))
    {
        struct s_ast_node *redirection = init_ast_node();
        while (read_redirection(redirection))
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

bool read_pipeline(struct s_ast_node *node)
{
    node->type = ND_PIPELINE;
    struct s_pipeline_node *pipeline = malloc(sizeof(struct s_pipeline_node));
    node->data.s_pipeline_node = pipeline;
    pipeline->nb_commands = 1;
    pipeline->commands = malloc(
            pipeline->nb_commands * sizeof(struct s_ast_node *));
    if ((pipeline->banged = (lexer_peek()->type == TK_BANG)))
        lexer_read();
    if (!read_compound_list(pipeline->commands[0]))
        return false;
    while (lexer_peek()->type == TK_OR)
    {
        while (lexer_read()->type == TK_NEWLINE)
            continue;
        pipeline->nb_commands++;
        pipeline->commands = realloc(pipeline->commands, pipeline->nb_commands *
                                                         sizeof(struct s_ast_node *));
        if (!read_compound_list(pipeline->commands[0]))
        {
            return false;
        }
    }
    return true;
}

bool read_and_or(struct s_ast_node *node)
{
    node->type = ND_AND_OR;
    struct s_and_or_node *and_or = malloc(sizeof(struct s_and_or_node));
    node->data.s_and_or_node = and_or;
    and_or->left = init_ast_node();
    and_or->type = ND_IF_NONE;
    and_or->right = NULL;
    if (!read_pipeline(and_or->left))
        return false;
    if (lexer_peek()->type == TK_AND_IF || lexer_peek()->type == TK_OR_IF)
    {
        if (lexer_peek()->type == TK_AND_IF)
            and_or->type = ND_AND_IF;
        else
            and_or->type = ND_OR_IF;
        while (lexer_read()->type == TK_NEWLINE)
            continue;
        and_or->right = init_ast_node();
        if (!read_pipeline(and_or->right))
            return false;
    }
    return true;
}

bool read_list(struct s_ast_node *node)
{
    node->type = ND_LIST;
    struct s_list_node *list = malloc(sizeof(struct s_list_node));
    list->left = init_ast_node();
    list->type = ND_LIST_NONE;
    list->right = NULL;
    if (!read_and_or(list->left))
        return false;
    if (lexer_peek()->type == TK_AND || lexer_peek()->type == TK_OR)
    {
        if (lexer_peek()->type == TK_AND)
            list->type = ND_AND;
        else
            list->type = ND_OR;
        list->right = init_ast_node();
        read_and_or(list->right);
    }
    return true;
}

bool read_input(struct s_ast_node *node)
{
    if (lexer_peek()->type == TK_NEWLINE || lexer_peek()->type == TK_EOF)
        return true;
    else if (read_list(node))
        return (lexer_peek()->type == TK_NEWLINE ||
                lexer_peek()->type == TK_EOF);
    else
        return false;
}
