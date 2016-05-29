/**
 ** @file argument_parser.h
 ** @brief Functions used to parse the input into the option structure
 ** @author Moisan L, Lees M
 */


#ifndef INC_42SH_ARGUMENT_PARSER_H
#define INC_42SH_ARGUMENT_PARSER_H

#include <global.h>

struct options
{
    int norc;
    int ast_print;
    int shopt_operation;
    char *command;
    char *shopt_option;
    char *file;
};

/**
 ** @fn is_command(char *name)
 ** @brief Checks wether the input string is a command or not
 ** @param the string to test
 ** @return 1 if it's a command, 0 otherwise
 */
int is_command(char *name);

/**
 ** @fn parse_options(int argc, char **argv, struct options *opt, int start)
 ** @brief Parses the input and filles the option struct
 ** @param the number of arguments
 ** @param the arguments as an array of strings
 ** @param the structure to be filled
 ** @param the position on which to start searching
 ** @return void
 */
void parse_options(int argc, char **argv, struct options *opt, int start);

/**
 ** @fn print_exit(int code, char *str, FILE *out)
 ** @brief Writes a message on a given stream and then exits using a given code
 ** @param the exit code
 ** @param the message to output
 ** @param the stream on which to write
 ** @return 1 but will never return except in case of error
 */
int print_exit(int code, char *str, FILE *out);

#endif
