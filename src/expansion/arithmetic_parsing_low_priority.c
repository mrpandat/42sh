#define _GNU_SOURCE

#include "../includes/global.h"
#include "../includes/expansion.h"

static struct s_art_node *read_unary_add_minus(struct s_stream *s)
{
    char op = stream_peek(s)[0];
    stream_read(s, 1);
    struct s_art_node *unop = init_art_node();
    unop->type = ART_UNOP;
    if (op == '+')
        unop->data.unop = init_unop_node(UNOP_ADD, read_a(s));
    else
        unop->data.unop = init_unop_node(UNOP_MINUS, read_a(s));
    return unop;
}

struct s_art_node *read_a(struct s_stream *s)
{
    read_spaces(s);
    if (strncmp("+", stream_peek(s), 1) == 0 || strncmp("-", stream_peek(s), 1) == 0)
        return read_unary_add_minus(s);
    else if (strncmp("(", stream_peek(s), 1) == 0)
    {
        stream_read(s, 1);
        struct s_art_node *node = read_j(s);
        if (strncmp(")", stream_peek(s), 1) == 0)
        {
            stream_read(s, 1);
            return node;
        }
        else
            return NULL;
    }
    else
    {
        struct s_art_node *num_node = read_num(s);
        return num_node;
    }
}

static struct s_art_node *read_unary_tilde_bang(struct s_stream *s)
{
    char op = stream_peek(s)[0];
    stream_read(s, 1);
    struct s_art_node *unop = init_art_node();
    unop->type = ART_UNOP;
    if ('!' == op)
        unop->data.unop = init_unop_node(UNOP_BANG, read_a(s));
    else
        unop->data.unop = init_unop_node(UNOP_INV, read_a(s));
    return unop;
}

struct s_art_node *read_b(struct s_stream *s)
{
    read_spaces(s);
    if (strncmp("!", stream_peek(s), 1) == 0 || strncmp("~", stream_peek(s), 1) == 0)
        return read_unary_tilde_bang(s);
    else if (strncmp("(", stream_peek(s), 1) == 0)
    {
        stream_read(s, 1);
        struct s_art_node *node = read_j(s);
        if (strncmp(")", stream_peek(s), 1) == 0)
        {
            stream_read(s, 1);
            return node;
        }
        else
            return NULL;
    }
    else
        return read_a(s);
}

struct s_art_node *read_c(struct s_stream *s)
{
    struct s_art_node *node = read_b(s);
    read_spaces(s);
    if (strncmp("**", stream_peek(s), 2) == 0)
    {
        stream_read(s, 2);
        struct s_art_node *binop = init_art_node();
        binop->type = ART_BINOP;
        binop->data.binop = init_binop_node(node,
                                            BINOP_POW,
                                            read_c(s));
        return binop;
    }
    else
        return node;
}

struct s_art_node *read_d(struct s_stream *s)
{
    struct s_art_node *node = read_c(s);
    read_spaces(s);
    if (strncmp("*", stream_peek(s), 1) == 0)
    {
        stream_read(s, 1);
        struct s_art_node *binop = init_art_node();
        binop->type = ART_BINOP;
        binop->data.binop = init_binop_node(node,
                                            BINOP_MULT,
                                            read_d(s));
        return binop;
    }
    else if (strncmp("/", stream_peek(s), 1) == 0)
    {
        stream_read(s, 1);
        struct s_art_node *binop = init_art_node();
        binop->type = ART_BINOP;
        binop->data.binop = init_binop_node(node,
                                            BINOP_DIV,
                                            read_d(s));
        return binop;
    }
    else
        return node;
}

struct s_art_node *read_e(struct s_stream *s)
{
    struct s_art_node *node = read_d(s);
    read_spaces(s);
    if (strncmp("+", stream_peek(s), 1) == 0)
    {
        stream_read(s, 1);
        struct s_art_node *binop = init_art_node();
        binop->type = ART_BINOP;
        binop->data.binop = init_binop_node(node,
                                            BINOP_ADD,
                                            read_e(s));
        return binop;
    }
    else if (strncmp("-", stream_peek(s), 1) == 0)
    {
        stream_read(s, 1);
        struct s_art_node *binop = init_art_node();
        binop->type = ART_BINOP;
        binop->data.binop = init_binop_node(node,
                                            BINOP_MINUS,
                                            read_e(s));
        return binop;
    }
    else
        return node;
}
