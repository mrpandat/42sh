#define _GNU_SOURCE

#include "../includes/global.h"
#include "../includes/expansion.h"
#include "../includes/util.h"

/*
struct s_art_node *read_f(struct s_stream *s)
{
    struct s_art_node *node = read_e(s);
    read_spaces(s);
    if ('&' == stream_peek(s)[0] && stream_peek(s)[1] != '&')
    {
        stream_read(s, 1);
        struct s_art_node *binop = init_art_node();
        binop->type = ART_BINOP;
        binop->data.binop = init_binop_node(node,
                                            BINOP_BIT_AND,
                                            read_f(s));
        return binop;
    }
    else
        return node;
}

struct s_art_node *read_g(struct s_stream *s)
{
    struct s_art_node *node = read_f(s);
    read_spaces(s);
    if (strncmp("^", stream_peek(s), 1) == 0)
    {
        stream_read(s, 1);
        struct s_art_node *binop = init_art_node();
        binop->type = ART_BINOP;
        binop->data.binop = init_binop_node(node,
                                            BINOP_BIT_XOR,
                                            read_g(s));
        return binop;
    }
    else
        return node;
}

struct s_art_node *read_h(struct s_stream *s)
{
    struct s_art_node *node = read_g(s);
    read_spaces(s);
    if ('|' == stream_peek(s)[0] && stream_peek(s)[1] != '|')
    {
        stream_read(s, 1);
        struct s_art_node *binop = init_art_node();
        binop->type = ART_BINOP;
        binop->data.binop = init_binop_node(node,
                                            BINOP_BIT_OR,
                                            read_h(s));
        return binop;
    }
    else
        return node;
}

struct s_art_node *read_i(struct s_stream *s)
{
    struct s_art_node *node = read_h(s);
    read_spaces(s);
    if (strncmp("&&", stream_peek(s), 2) == 0)
    {
        stream_read(s, 2);
        struct s_art_node *binop = init_art_node();
        binop->type = ART_BINOP;
        binop->data.binop = init_binop_node(node,
                                            BINOP_BOOL_AND,
                                            read_i(s));
        return binop;
    }
    else
        return node;
}

struct s_art_node *read_j(struct s_stream *s)
{
    struct s_art_node *node = read_i(s);
    read_spaces(s);
    if (strncmp("||", stream_peek(s), 1) == 0)
    {
        stream_read(s, 2);
        struct s_art_node *binop = init_art_node();
        binop->type = ART_BINOP;
        binop->data.binop = init_binop_node(node,
                                            BINOP_BOOL_OR,
                                            read_j(s));
        return binop;
    }
    else
        return node;
}
*/
