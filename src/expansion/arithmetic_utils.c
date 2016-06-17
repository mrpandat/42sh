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
