#include "../includes/global.h"
#include "../includes/hashtable.h"
#include "../includes/builtins.h"

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

    return 0;
}

bool is_alias(char *command)
{
    if (NULL == g_env.aliases)
        return false;

    if (NULL != ht_get(g_env.aliases, command))
        return true;

    return false;
}

int my_alias(struct s_simple_command_node *node)
{
    if (node->nb_elements != 1)
        return alias_list_all();

    if (node->nb_elements != 3)
        return 1;

    // FIXME: Assuming node data is correct
    if (NULL == g_env.aliases)
        g_env.aliases = ht_init(200, free);

    ht_insert(g_env.aliases, node->elements[1]->data.word,
              node->elements[2]->data.word);

    return 0;
}

int my_unalias(struct s_simple_command_node *node)
{
    if (node->nb_elements != 2)
        return 1;

    // FIXME: Assuming node data is correct
    if (NULL == g_env.aliases)
        g_env.aliases = ht_init(200, free);

    ht_insert(g_env.aliases, node->elements[1]->data.word,
              node->elements[2]->data.word);

    return 0;
}

