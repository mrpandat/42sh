#include <parser.h>

#include <fcntl.h>
#include "includes/hashtable.h"
#include "includes/execute.h"


void fill_env(struct s_lexer *lexer, struct s_ast_node *root,
              struct options opt)
{
    g_env.lexer = lexer;
    g_env.root = root;
    g_env.HOME = getenv("HOME");
    g_env.PWD = getenv("PWD");
    g_env.OLDPWD = getenv("OLDPWD");
    g_env.aliases = ht_init(100, free);
    g_env.variables = ht_init(100, free);
    g_env.opt = &opt;
    g_env.ast_print = 0;
    g_env.dotglob = 0;
    g_env.expand_aliases = 0;
    g_env.extglob = 0;
    g_env.nocaseglob = 0;
    g_env.nullglob = 0;
    g_env.sourcepath = 0;
    g_env.xpg_echo = 0;
    g_env.words = NULL;
    g_env.n_words = 0;
}

int main(int argc, char *argv[])
{
    struct options opt = {0, 0, "", ""};
    parse_options(argc, argv, &opt, 1);
    struct s_lexer *lexer = lexer_init(opt.command);
    lexer_process(lexer);
    struct s_ast_node *root = parser(lexer);
    if (root == NULL)
    {
        if (strcmp(opt.file, "") != 0)
            free(opt.command);
        fprintf(stderr, "Bad grammar\n");
        return 1;
    }
    if (opt.ast_print)
        print_ast(root);
    fill_env(lexer, root, opt);
    return execute(opt, root, lexer);
}
