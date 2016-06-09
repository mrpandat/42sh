#include "global.h"
#include "ast.h"

void free_element_node(struct s_element_node *node)
{
    if (node == NULL)
        return;
    else if (node->type == EL_REDIRECTION)
        free_redirection_node(node->data.s_redirection_node);
    else if (node->type == EL_WORD)
        free_word(node->data.s_word);
    free(node);
}

void free_word(struct s_word *word)
{
    if (word == NULL)
        return;
    free(word);
}
