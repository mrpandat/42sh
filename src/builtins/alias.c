#include "builtins.h"


bool is_alias(char *command)
{
    (void) command;
    return false;
}

int my_alias(struct s_simple_command_node *node)
{
    (void) node;
    return 0;
}

