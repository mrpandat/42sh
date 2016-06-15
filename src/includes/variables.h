/**
 ** @file variables.h
 ** @brief variables for 42sh
 ** @author Treibert Jean
 */


#ifndef INC_42SH_VAR_H
#define INC_42SH_VAR_H

#include "global.h"

int is_var_assign(char *word, int save);
int is_variable(struct s_simple_command_node *node);


#endif
