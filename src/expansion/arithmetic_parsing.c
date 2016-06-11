#define _GNU_SOURCE

#include <expansion.h>
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

struct s_art_node *init_art_node()
{
    return malloc(sizeof(struct s_art_node));
}

struct s_binop_node *init_binop_node(struct s_art_node *left,
                                     enum e_binop_type type,
                                     struct s_art_node *right)
{
    struct s_binop_node *node = malloc(sizeof (struct s_binop_node));
    node->left = left;
    node->type = type;
    node->right = right;
    return node;
}

struct s_unop_node *init_unop_node(enum e_unop_type type,
                                   struct s_art_node *son)
{
    struct s_unop_node *node = malloc(sizeof (struct s_unop_node));
    node->type = type;
    node->number = son;
    return node;
}

struct s_number_node *init_num_node_int(int num)
{
    struct s_number_node *node = malloc(sizeof (struct s_number_node));
    node->type = NUM_INT;
    node->data.integer = num;
    return node;
}

void free_binop_node(struct s_binop_node *node)
{
    free_art_node(node->left);
    free_art_node(node->right);
    free(node);
}

void free_unop_node(struct s_unop_node *node)
{
    free_art_node(node->number);
    free(node);
}

void free_num_node(struct s_number_node *node)
{
    free(node);
    return;
}

void free_art_node(struct s_art_node *node)
{
    if (node->type == ART_NUM)
        free_num_node(node->data.number);
    else if (node->type == ART_BINOP)
        free_binop_node(node->data.binop);
    else if (node->type == ART_UNOP)
        free_unop_node(node->data.unop);
    free(node);
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

struct s_art_node *read_a(struct s_stream *s)
{
    read_spaces(s);
    if (strncmp("+", stream_peek(s), 1) == 0 || strncmp("-", stream_peek(s), 1) == 0)
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

struct s_art_node *read_b(struct s_stream *s)
{
    read_spaces(s);
    if (strncmp("!", stream_peek(s), 1) == 0 || strncmp("~", stream_peek(s), 1) == 0)
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
