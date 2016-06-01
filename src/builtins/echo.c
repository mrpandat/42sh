#include <builtins.h>

void my_echo(struct s_simple_command_node *node)
{
    for (int i = 0; i < node->nb_elements; i++){
        if(node->elements[i]->type == EL_WORD)
            printf("%s",node->elements[i]->data.word);
    }
}
