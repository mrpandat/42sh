#include "global.h"
#include "ast.h"

struct s_if_node *init_if_node(void)
{
    struct s_if_node *node = malloc(sizeof (struct s_if_node));
    node->false_statement = NULL;
    node->true_statement = init_ast_node();
    node->predicate = init_ast_node();
    return node;
}

struct s_case_node *init_case_node(char *word)
{
    struct s_case_node *node = malloc(sizeof (struct s_case_node));
    node->word = word;
    node->nb_items = 0;
    node->items = NULL;
    return node;
}

void add_case_item(struct s_case_node *node, struct s_case_item_node *item)
{
    node->nb_items++;
    node->items = realloc(node->items,
                          node->nb_items * sizeof (struct s_case_item_node));
    node->items[node->nb_items - 1] = item;
}

struct s_case_item_node *init_case_item_node(void)
{
    struct s_case_item_node *node = malloc(sizeof (struct s_case_item_node));
    node->nb_words = 0;
    node->statement = init_ast_node();
    node->words = NULL;
    return node;
}

void add_case_item_word(struct s_case_item_node *item, char *word)
{
    item->nb_words++;
    item->words = realloc(item->words, item->nb_words * sizeof (char *));
    item->words[item->nb_words - 1] = word;
}
