#include "global.h"
#include "ast.h"

struct s_element_node *init_element_node(void)
{
    struct s_element_node *node = malloc(sizeof (struct s_element_node));
    node->type = EL_NONE;
    return node;
}

struct s_word *init_word(enum e_word_type type, char *value)
{
    struct s_word *word = malloc(sizeof (struct s_word));
    word->type = type;
    word->value = value;
    return word;
}

