#include "global.h"
#include "ast.h"

struct s_while_node *init_while_node(void)
{
    struct s_while_node *node = malloc(sizeof (struct s_while_node));
    node->predicate = init_ast_node();
    node->statement = init_ast_node();
    return node;
}

struct s_until_node *init_until_node(void)
{
    struct s_until_node *node = malloc(sizeof (struct s_until_node));
    node->predicate = init_ast_node();
    node->statement = init_ast_node();
    return node;
}

struct s_for_node *init_for_node(char *iterator)
{
    struct s_for_node *node = malloc(sizeof (struct s_for_node));
    node->iterator = iterator;
    node->nb_words = 0;
    node->words = NULL;
    node->do_group = init_ast_node();
    return node;
}

void add_for_word(struct s_for_node *node, char *word)
{
    node->nb_words++;
    node->words = realloc(node->words, node->nb_words * sizeof (char *));
    node->words[node->nb_words - 1] = word;
}
