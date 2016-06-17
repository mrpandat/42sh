#define _GNU_SOURCE

#include "../includes/global.h"
#include "../includes/expansion.h"
#include "../includes/util.h"

struct s_art_node *read_num(struct s_stream *s)
{
    read_spaces(s);
    int i = 0;
    char c = stream_peek(s)[0];
    while (c != '\0' && c >= '0' && c <= '9')
    {
        i++;
        c = stream_peek(s)[i];
    }
    char *char_num = strndup(stream_peek(s), i);
    int num = atoi(char_num);
    stream_read(s, i);
    free(char_num);
    struct s_art_node *node = init_art_node();
    node->type = ART_NUM;
    node->data.number = init_num_node_int(num);
    return node;
}

struct s_art_node *read_var(struct s_stream *s)
{
    read_spaces(s);
    int i = 0;
    char c = stream_peek(s)[0];
    while (c != '\0' && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
                         || (c >= 'A' && c <= 'Z')))
    {
        i++;
        c = stream_peek(s)[i];
    }
    char *var = strndup(stream_peek(s), i);
    char *var_value = get_var(var);
    if (var_value == NULL)
    {
        free(var);
        return NULL;
    }
    stream_read(s, i);
    int num = atoi(var_value);
    free(var_value);
    struct s_art_node *node = init_art_node();
    node->type = ART_NUM;
    node->data.number = init_num_node_int(num);
    return node;
}

