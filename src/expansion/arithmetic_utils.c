#define _GNU_SOURCE

#include "../includes/global.h"
#include "../includes/expansion.h"
#include "../includes/util.h"

char *stream_peek(struct s_stream *stream)
{
    return stream->content + stream->pos;
}

void stream_read(struct s_stream *stream, int n)
{
    stream->pos += n;
}

void read_spaces(struct s_stream *s)
{
    while (strncmp(stream_peek(s), " ", 1) == 0)
        stream_read(s, 1);
}

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

char *arithmetic_expansion(char *expression)
{
    struct s_stream *s = malloc(sizeof (struct s_stream));
    s->content = expression;
    s->pos = 0;
    struct s_art_node *root = read_j(s);
    free(s);
    if (root != NULL)
    {
        int res = execute_art_node(root);
        free_art_node(root);
        return my_itoa(res);
    }
    else
        return "";
}
