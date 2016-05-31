#include <parser.h>
#include <sys/wait.h>
#include "includes/execute.h"
#include "includes/global.h"
#include "includes/argument_parser.h"


int main(int argc, char *argv[])
{
    struct options opt = {0, 0, 0, "", "", ""};
    parse_options(argc, argv, &opt, 1);
    struct s_lexer *lexer = lexer_init(opt.command);
    lexer_process(lexer);
    struct s_ast_node *root = parser(lexer);
    if (root == NULL)
        return 1;
    execute(opt, root, lexer);
    return 0;
}

