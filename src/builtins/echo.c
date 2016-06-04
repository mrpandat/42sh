#include <builtins.h>
#include <asm/errno.h>

static int execute_long_option(struct s_simple_command_node *node, int i,
                        struct echo_struct *echo)
{
    if (node->nb_elements == 2)
    {
        if (!strcmp("--version", node->elements[i]->data.word)
            && echo->options == 0)
        {
            printf("Version: 0.1\n");
            return 0;
        }
        if (!strcmp("--help", node->elements[i]->data.word)
            && echo->options == 0)
        {
            printf("Version: 0.1.\n Ecrit par Treibert "
                           "Jean.\n");
            return 0;
        }
    }
    return 1;
}

static int execute_short_options(struct s_simple_command_node *node, int i,
                                struct
        echo_struct *echo)
{
    if (!strcmp("-n", node->elements[i]->data.word) && echo->noption == 0)
    {
        echo->noption = 1;
        echo->options++;
        return 0;
    }
    if (!strcmp("-e", node->elements[i]->data.word) && echo->Eoption == 0)
    {
        echo->eoption = 1;
        echo->options++;
        return 0;
    }
    if (!strcmp("-E", node->elements[i]->data.word) && echo->eoption == 0)
    {
        echo->Eoption = 1;
        echo->options++;
        return 0;
    }
    return 1;
}

static int print_word_escaped(char *word)
{
    if (!strcmp(word, "\\c"))
        return 1;
    else if (!strcmp(word, "\\a"))
        putchar('\a');
    else if (!strcmp(word, "\\b"))
        putchar('\b');
    else if (!strcmp(word, "\\e"))
        putchar('\033');
    else if (!strcmp(word, "\\f"))
        putchar('\f');
    else if (!strcmp(word, "\\n"))
        putchar('\n');
    else if (!strcmp(word, "\\r"))
        putchar('\r');
    else if (!strcmp(word, "\\t"))
        putchar('\t');
    else if (!strcmp(word, "\\v"))
        putchar('\v');
    else
        printf("%s", word);
    return 0;
}

int print_word_not_escaped(char *word)
{
    if (!strcmp(word, "\\c"))
        return 1;
    else if (!strcmp(word, "\\a"))
        putchar('a');
    else if (!strcmp(word, "\\b"))
        putchar('b');
    else if (!strcmp(word, "\\e"))
        putchar('e');
    else if (!strcmp(word, "\\f"))
        putchar('f');
    else if (!strcmp(word, "\\n"))
        putchar('n');
    else if (!strcmp(word, "\\r"))
        putchar('r');
    else if (!strcmp(word, "\\t"))
        putchar('t');
    else if (!strcmp(word, "\\v"))
        putchar('v');
    else
        printf("%s", word);
    return 0;
}

static int exit_free(struct echo_struct *echo)
{
    free(echo);
    return 0;
}

int my_echo(struct s_simple_command_node *node)
{
    int words = 0;
    struct echo_struct *echo = malloc(sizeof(struct echo_struct));
    echo->Eoption = 0;
    echo->eoption = 0;
    echo->noption = 0;
    echo->options = 0;
    for (int i = 1; i < node->nb_elements; i++)
        if (node->elements[i]->type == EL_WORD)
        {
            if (words == 0)
            {
                if (execute_long_option(node, i, echo) == 0) return exit_free(echo);
                if (execute_short_options(node, i, echo) == 0) continue;
            }
            if (words != 0) printf(" ");
            if (echo->eoption == 1)
            {
                if (print_word_escaped(node->elements[i]->data.word) == 1)
                    return exit_free(echo);
            }
            else print_word_not_escaped(node->elements[i]->data.word);
            words++;
        }
    if (echo->noption == 0)
        putchar('\n');
    return exit_free(echo);
}
