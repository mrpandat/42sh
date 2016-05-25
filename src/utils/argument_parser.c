#define _GNU_SOURCE 1

#include <global.h>
#include <argument_parser.h>


void help(char *name)
{
    fprintf(stderr, "%s [ GNU long options ] [ options ] [ file ]\n", name);
}

int is_command(char *name)
{
    if (strcmp(name, "-v") == 0 || strcmp(name, "--version") == 0
        || strcmp(name, "-c") == 0
        || strcmp(name, "--command") == 0 || strcmp(name, "--norc") == 0
        || strcmp(name, "--ast-print") == 0)
        return 1;
    else
        return 0;
}

int parse_command(char **argv, int i, struct options *options1)
{
    i++;
    options1->command = argv[i];
    return i;
}

int print_exit(int code, char *str)
{
    fprintf(stderr, "%s\n", str);
    exit(code);
}

int match(char *compare, char *compare2)
{
    if (strlen(compare) > strlen(compare2))
        for (unsigned x = 0; x < strlen(compare2); x++)
            if (compare2[x] != compare[x])
                return 0;
    return 1;
}

void parse_long_option(char **argv, struct options *options, int i)
{
    int ok = 1;
    if (argv[i][2] == 'n') //norc
    {
        char *compare = "--norc";
        ok = match(compare, argv[i]);
        if (match(compare, argv[i]) == 1)
            options->norc = 1;
    }
    else if (argv[i][2] == 'a') //ast-print
    {
        char *compare = "--ast-print";
        ok = match(compare, argv[i]);
        if (ok == 1)
            options->ast_print = 1;
    }
    else if (argv[i][2] == 'v') // version
    {
        char *compare = "--version";
        ok = match(compare, argv[i]);
        if (ok == 1)
            print_exit(0, "Version 0.5");
    }
    if (ok == 0)
        fprintf(stderr, "unknown long option : %s\n", argv[i]);
}

/**
 * Checks if the file is correct
 */
void check_correct(int argc)
{
    if (argc < 2)
        print_exit(-1,"42sh [ GNU long options ] [ options ] [ file ]");
}

void parse_options(int argc, char **argv, struct options *options, int start)
{
    check_correct(argc);
    for (int i = start; i < argc; i++)
        if (strcmp(argv[i], "--norc") == 0)
            options->norc = 1;
        else if (strcmp(argv[i], "--ast-print") == 0)
            options->ast_print = 1;
        else if (strcmp(argv[i], "-v") == 0
                 || strcmp(argv[i], "--version") == 0)
            print_exit(0, "Version 0.5");
        else if (strcmp(argv[i], "-c") == 0)
            i = parse_command(argv, i, options);
        else if ((argv[i][0] == '-' || argv[i][0] == '+')
                 && argv[i][1] == '0')
        {
            options->shopt_operation = (argv[i][0] == '+' ? 1 : -1);
            i++;
            options->shopt_option = argv[i];
        }
        else if (argv[i][0] == '-' && argv[i][1] == '-')
            parse_long_option(argv, options, i);
        else if (i == argc - 1)
            options->file = argv[i];
        else
            print_exit(-1, "unknown option");
}
