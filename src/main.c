#include "includes/execute.h"
#include "includes/global.h"
#include "includes/argument_parser.h"

int main(int argc, char *argv[])
{
    struct options opt = {0, 0, 0, "", "", ""};
    parse_options(argc, argv, &opt, 1);
    if (strcmp(opt.command, "") == 0)
    {
        print_exit(-1, "42sh [ GNU long options ] [ options ] [ file ]", stderr);
        return -1;
    }

    execute(opt);
    return 0;
}

