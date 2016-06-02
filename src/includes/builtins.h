#ifndef INC_42SH_EXIT_H
#define INC_42SH_EXIT_H
# include <global.h>
# include <ast.h>

int my_exit(struct s_simple_command_node *node);
void my_echo(struct s_simple_command_node *node);
int my_cd(struct s_simple_command_node *node);
#endif //INC_42SH_EXIT_H
