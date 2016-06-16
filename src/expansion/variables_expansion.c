#define _GNU_SOURCE

#include <util.h>
#include <hashtable.h>
#include <ast.h>
#include <execute.h>
#include <expansion.h>

/*
 * il manque ici un ht_check pour voir si la variable existe,
 * sinon ça throw un bad_access
 */
char *get_var(char *name)
{
    struct s_element *a = ht_get(g_env.variables, name);
    return a->value;
}

void set_var(char *var, void *value)
{
    ht_insert(g_env.variables, var, value);
}

int exit_var(int vcount, int values, int save, char *var, char *value)
{
    if (vcount == 0) return 1;
    if (values == 0) return 2;
    if (save == 1) set_var(var, value);
    return 0;
}

int is_var_assign(char *word, int save)
{
    int values = 0, vcount = 0;
    char *var = strdup(""), *value = strdup("");
    for (size_t i = 0; i < strlen(word); i++)
    {
        if (word[i] == '\0') break;
        if (word[i] == '=')
        {
            vcount++;
            continue;
        }
        if (vcount == 0)
            var = str_append_char(var, word[i]);
        else
        {
            value = str_append_char(value, word[i]);
            values++;
        }
    }
    return exit_var(vcount, values, save, var, value);
}

char *get_var_name(char *word) {
    int values = 0, vcount = 0;
    char *var = strdup(""), *value = strdup("");
    for (size_t i = 0; i < strlen(word); i++)
    {
        if (word[i] == '\0') break;
        if (word[i] == '=')
        {
            vcount++;
            break;
        }
        var = str_append_char(var, word[i]);

    }
    exit_var(vcount, values, 0, var, value);
    return var;
}

int variables(struct s_simple_command_node *node)
{
    char* var_name = strdup("");
    for (int i = 0; i < node->nb_elements; i++)
    {
        if (node->elements[i]->type != EL_WORD) continue;
        char *word = exec_word(node->elements[i]->data.s_word);
        if(is_var_assign(word,0) == 0 && i == 0)
            return is_var_assign(word,1);
        else if(is_var_assign(word,0) == 2 && i == 0){
            var_name = get_var_name(word);
        }
        else if(i == 1) set_var(var_name,word);

        else return 1;
    }
    return 0;
}

