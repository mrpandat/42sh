#define _GNU_SOURCE

#include <global.h>
#include "../includes/execute.h"
#include "../includes/expansion.h"

static int exec_loops_control_node(struct s_ast_node *node)
{
    enum e_node_type type = node->type;
    if (type == ND_IF)
        return exec_if_node(node->data.s_if_node);
    else if (type == ND_WHILE)
        return exec_while_node(node->data.s_while_node);
    else if (type == ND_UNTIL)
        return exec_until_node(node->data.s_until_node);
    else if (type == ND_CASE)
        return exec_case_node(node->data.s_case_node);
    else if (type == ND_FOR)
        return exec_for_node(node->data.s_for_node);
    else
        return -1;
}

int exec_ast_node(struct s_ast_node *node)
{
    if (node == NULL)
        return -1;
    enum e_node_type type = node->type;
    if (type == ND_COMMAND)
        return exec_command_node(node->data.s_command_node);
    else if (type == ND_REDIRECTION)
        return exec_redirection_node(node->data.s_redirection_node);
    else if (type == ND_FUNCDEC)
        return exec_funcdec_node(node->data.s_funcdec_node);
    else if (type == ND_SIMPLE_COMMAND)
        return exec_simple_command_node(node->data.s_simple_command_node);
    else if (type == ND_PIPELINE)
        return exec_pipeline_node(node->data.s_pipeline_node);
    else if (type == ND_AND_OR)
        return exec_and_or_node(node->data.s_and_or_node);
    else if (type == ND_LIST)
        return exec_list_node(node->data.s_list_node);
    else
        return exec_loops_control_node(node);
}

int exec_redirection_node(struct s_redirection_node *node)
{
    // TODO: Implement redirection
    if (node == NULL)
        return -1;
    return -1;
}

char *tilde_expansion(char *word)
{
    if (!strcmp("~", word))
        return g_env.HOME;
    else if (!strcmp("~-", word))
        return g_env.OLDPWD;
    else if (!strcmp("~+", word))
        return g_env.PWD;
    return NULL;
}

static char *execute_subshell(char *expression)
{
    return strdup(expression);
}

static char *exec_normal_word(struct s_word *word)
{
    char *expanded;
    if (word->type != WD_ESC
        && ((expanded = expand_path(word->value)) != NULL
            || (expanded = expand_tilde(word->value)) != NULL))
    {
        word->type = WD_PATH;
        word->result = expanded;
        return word->result;
    }
    else if ((expanded = get_var(word->value)) != NULL)
        return expanded;
    else
        return word->value;
}

static char *handle_arith_subshell(struct s_word *word)
{
    if (word->result != NULL)
    {
        g_env.n_words++;
        g_env.words = realloc(g_env.words, g_env.n_words * sizeof (char*));
        g_env.words[g_env.n_words - 1] = word->result;
    }
    if (word->type == WD_ARITH)
        word->result = arithmetic_expansion(word->value);
    else
        word->result = execute_subshell(word->value);
    return word->result;
}

char *exec_word(struct s_word *word)
{
    if (word->type == WD_WORD || word->type == WD_ESC
        || word->type == WD_ASSIGNEMENT_WORD)
        return exec_normal_word(word);
    else if (word->type == WD_PATH)
        return word->result;
    else if (word->type == WD_ARITH || word->type == WD_SUBSHELL)
        return handle_arith_subshell(word);
    else if (word->type == WD_VARIABLE)
    {
        if (get_var(word->value) == NULL)
            return "";
        else
            return get_var(word->value);
    }
    else
        return NULL;
}
