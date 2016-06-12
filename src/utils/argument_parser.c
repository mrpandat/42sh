#define _GNU_SOURCE 1

#include <global.h>
#include <argument_parser.h>
#include <util.h>
#include <execute.h>
#include <builtins.h>
#include <sys/stat.h>


int parse_command(char **argv, int i, struct options *options1)
{
    i++;
    options1->command = argv[i];
    return i;
}

int print_exit(int code, char *str, FILE *out)
{
    fprintf(out, "%s\n", str);
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
            print_exit(0, "Version 0.8", stdout);
    }
    if (ok == 0)
        fprintf(stderr, "unknown long option : %s\n", argv[i]);
}

void parse_file(struct options *options)
{
    if (strcmp(options->command, "") == 0
        && strcmp(options->file, "") != 0)
    {
        if (file_test(options->file) == 127)
            print_exit(127, "No such file or directory", stderr);
        options->command = path_to_str(options->file);
    }
    else
        options->file = "";

}

int shopt_parse(int i, char **argv)
{
    set_option(argv[i + 1], (argv[i][0] == '+' ? 1 : -1));
    return i + 1;
}

void parse_small_options(int argc, char **argv, struct options *options,
                         int start)
{
    for (int i = start; i < argc; i++)
        if (strcmp(argv[i], "--norc") == 0)
            options->norc = 1;
        else if (strcmp(argv[i], "--ast-print") == 0)
            options->ast_print = 1;
        else if (strcmp(argv[i], "-v") == 0
                 || strcmp(argv[i], "--version") == 0)
            print_exit(0, "Version 0.8", stdout);
        else if (strcmp(argv[i], "-h") == 0)
            print_exit(0, "42sh [ GNU long options ] [ options ] [ file ]",
                       stdout);
        else if (strcmp(argv[i], "-c") == 0)
            i = parse_command(argv, i, options);
        else if ((argv[i][0] == '-' || argv[i][0] == '+')
                 && argv[i][1] == 'O')
            i = shopt_parse(i, argv);
        else if (argv[i][0] == '-' && argv[i][1] == '-') // long option
            parse_long_option(argv, options, i);
        else if (i == argc - 1)
            options->file = argv[i];
        else
            print_exit(1, "unknown option", stderr);
}

void parse_options(int argc, char **argv, struct options *options, int start)
{
    if (isatty(STDIN_FILENO))
    {
        parse_small_options(argc, argv, options, start);
        parse_file(options);
    }
    else
    {
        struct stat st_info;
        fstat(0, &st_info);
        if (S_ISFIFO(st_info.st_mode))
        {
            // pipe = don't care
            parse_small_options(argc, argv, options, start);
            parse_file(options);
        }
        else
        {
            options->file = "stdin";
            options->command = file_to_str(stdin);
        }
    }

}
