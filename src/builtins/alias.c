#define _GNU_SOURCE

#include <execute.h>
#include "../includes/hashtable.h"
#include "../includes/builtins.h"

static bool is_alias(char *command)
{
    if (NULL == g_env.aliases)
        return false;

    if (NULL != ht_get(g_env.aliases, command))
        return true;

    return false;
}

static int alias_list_all()
{
    if (NULL == g_env.aliases)
        return 0;

    int listsize = ht_size(g_env.aliases);
    struct s_element **aliases = ht_get_all(g_env.aliases);

    if (0 == listsize || NULL == aliases)
        return 0;

    for (int i = 0; i < listsize; ++i)
    {
        printf("alias %s='%s'\n", aliases[i]->key, (char *) aliases[i]->value);
    }

    free(aliases);

    return 0;
}

static void alias_set_value(struct s_element_node *element,
                            struct s_element_node *esc_val)
{
    if (NULL == g_env.aliases)
        return;

    char *buf = strdup(exec_word(element->data.s_word));

    char *key = strtok(buf, "=");
    char *raw_value = strtok(NULL, "=");
    char *value;

    if (NULL == raw_value && NULL != esc_val)
        raw_value = strdup(exec_word(esc_val->data.s_word));

    if (NULL != raw_value)
    {
        if (0 == strncmp("\"", raw_value, 1)
            || 0 == strncmp("\'", raw_value, 1))
        {
            raw_value++;
            value = strndup(raw_value, strlen(raw_value) - 1);
        }
        else
            value = strdup(raw_value);

        ht_insert(g_env.aliases, key, value);
        free(value);
    }
    if (NULL != esc_val)
        free(raw_value);
    free(buf);
}

static bool alias_get_value(char *command)
{
    if (NULL == g_env.aliases || !is_alias(command))
    {
        fprintf(stderr, "-42sh: alias: %s: not found\n", command);
        return false;
    }

    struct s_element *alias = ht_get(g_env.aliases, command);

    printf("alias %s='%s'\n", alias->key, (char *) alias->value);

    return true;
}

int my_alias(struct s_simple_command_node *node)
{
    if (node->nb_elements == 1)
        return alias_list_all();

    int ret = 0;

    for (int i = 1; i < node->nb_elements; ++i)
    {
        char *tmp = strdup(exec_word(node->elements[i]->data.s_word));
        char *key = strtok(tmp, "=");
        char *val = strtok(NULL, "=");
        if (NULL != key)
        {
            if (NULL == val)
            {
                alias_set_value(node->elements[i], node->elements[i + 1]);
                i++;
            }
                /** value has no quoting */
            else
                alias_set_value(node->elements[i], NULL);
        }
        else
        {
            if (!alias_get_value(exec_word(node->elements[i]->data.s_word)))
                ret = 1;
        }
        free(tmp);
    }

    return ret;
}

int my_unalias(struct s_simple_command_node *node)
{
    if (node->nb_elements == 1)
    {
        fprintf(stderr, "unalias: usage: unalias [-a] name [name ...]\n");
        return 2;
    }

    if (NULL == g_env.aliases)
        return 0;

    if (0 == strcmp("-a", exec_word(node->elements[1]->data.s_word)))
    {
        ht_remove_all(g_env.aliases);
        return 0;
    }

    int ret = 0;

    for (int i = 1; i < node->nb_elements; ++i)
    {
        char *alias = exec_word(node->elements[i]->data.s_word);
        if (NULL == ht_get(g_env.aliases, alias))
        {
            fprintf(stderr, "-42sh: unalias: %s: not found\n", alias);
            ret = 1;
        }
        else
            ht_remove(g_env.aliases, alias);
    }

    return ret;
}

