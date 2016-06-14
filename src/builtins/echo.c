#include <builtins.h>
#include <execute.h>

static int exitf(struct echo_struct *echo)
{
    free(echo);
    return 0;
}

static int execute_long_option(struct s_simple_command_node *node, int i,
                               struct echo_struct *echo)
{
    if (node->nb_elements == 2)
    {
        if (!strcmp("--version", exec_word(node->elements[i]->data.s_word))
            && echo->options == 0)
        {
            printf("Version: 1.0\n");
            return 0;
        }
        if (!strcmp("--help", exec_word(node->elements[i]->data.s_word))
            && echo->options == 0)
        {
            printf("Version: 0.1.\n Ecrit par Treibert Jean.\n");
            return 0;
        }
    }
    return 1;
}

void changeEchoOption(int noption, int eoption, int Eoption,
                      struct echo_struct *echo) {
    if(noption == 1) {
        echo->noption = 1;
        echo->options++;
    }
    if(eoption == 1)
    {
        echo->eoption = 1;
        echo->Eoption = 0;
        echo->options++;
    }
    if(Eoption == 1)
    {
        echo->eoption = 0;
        echo->Eoption = 1;
        echo->options++;
    }

}

static int execute_short_options(struct s_simple_command_node *node, int i,
                                 struct echo_struct *echo)
{
    char *ew = exec_word(node->elements[i]->data.s_word);
    if (ew[0] != '-') return 1;
    for (size_t j = 1; j < strlen(ew); j++)
    {
        if (ew[j] == '\0') return 0;
        switch (ew[j])
        {
            case 'n':
                changeEchoOption(1,0,0,echo);
                break;
            case 'e':
                changeEchoOption(0,1,0,echo);
                break;
            case 'E':
                changeEchoOption(0,0,1,echo);
                break;
            default:
                return 1;
        }
    }
    return 0;
}

static int pr_escaped(char *word)
{
    for (size_t i = 0; i < strlen(word); i++)
    {
        size_t sw = strlen(word);
        if (word[i] == '\0') return 0;
        if (word[i] == '\\' && sw >= i + 1)
        {
            if (word[i + 1] == 'c') return 1;
            else if (word[i + 1] == 'a') printf("\a");
            else if (word[i + 1] == 'b') printf("\b");
            else if (word[i + 1] == 'f') printf("\f");
            else if (word[i + 1] == 'n') printf("\n");
            else if (word[i + 1] == 'r') printf("\r");
            else if (word[i + 1] == 't') printf("\t");
            else if (word[i + 1] == 'v') printf("\v");
            else
            {
                putchar('\\');
                putchar(word[i + 1]);
            }
            i++;
        }
        else
            putchar(word[i]);
    }
    return 0;
}

static int print_word_not_escaped(char *word, int words)
{
    if (words >= 1) printf(" ");
    if (!strcmp(word, "\\c"))
        return 1;
    if (strlen(word) >= 1 && word[0] == '\\')
    {
        for (size_t i = 1; i < strlen(word); i++)
            printf("%c", word[i]);
    } else
        printf("%s", word);

    return 0;
}


struct echo_struct *fill_echo()
{
    struct echo_struct *echo = malloc(sizeof(struct echo_struct));
    echo->Eoption = 0;
    echo->eoption = 0;
    echo->noption = 0;
    echo->options = 0;
    return echo;
}


int my_echo(struct s_simple_command_node *node)
{
    int words = 0;
    struct echo_struct *echo = fill_echo();
    for (int i = 1; i < node->nb_elements; i++)
    {
        if (node->elements[i]->type != EL_WORD) continue;
        char *word = exec_word(node->elements[i]->data.s_word);
        if (node->elements[i]->data.s_word->type == WD_ESC)
        {
            if (echo->eoption == 0) fprintf(stdout, "%s", word);
            else if (pr_escaped(word) == 1) return exitf(echo);
            if (words != 0) printf(" ");
        }
        else
        {
            if (words == 0)
            {
                if (execute_long_option(node, i, echo) == 0) return exitf(echo);
                if (execute_short_options(node, i, echo) == 0) continue;
            }
            print_word_not_escaped(word, words);
            words++;
        }
    }
    if (echo->noption == 0) putchar('\n');
    return exitf(echo);
}
