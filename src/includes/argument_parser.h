#ifndef INC_42SH_ARGUMENT_PARSER_H
#define INC_42SH_ARGUMENT_PARSER_H

struct options
{
    int norc;
    int ast_print;
    int shopt_operation;
    char *command;
    char *shopt_option;
};

void help(char *name);

int is_command(char *name);

void parse_options(int argc, char **argv, struct options *opt, int start);
#endif
