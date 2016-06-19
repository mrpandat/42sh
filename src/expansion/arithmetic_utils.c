#define _GNU_SOURCE

#include <arith_lexer.h>
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
    struct s_arlex *lexer = arlex_init(expression);
    arlex_process(lexer);
    if (lexer == NULL)
        return NULL;
    struct s_stream *s = malloc(sizeof (struct s_stream));
    s->content = expression;
    s->pos = 0;
    struct s_art_node *root = shunting_yard(lexer); //read_j(s);
    free(s);
    if (root != NULL)
    {
        int res = execute_art_node(root);
        free_art_node(root);
        arlex_destroy(lexer);
        return my_itoa(res);
    }
    else
        return "";
}

struct s_art_stack *init_stack(void)
{
    struct s_art_stack *stack = malloc(sizeof (struct s_art_stack));
    stack->size = 0;
    stack->elements = NULL;
    return stack;
}


void free_stack(struct s_art_stack *stack)
{
    for (int i = 0; i < stack->size; i ++)
    {   if (stack->elements[i] != NULL)
            free(stack->elements[i]);
    }
    if (stack->elements != NULL)
        free(stack->elements);
    free(stack);
}

void add_stack(struct s_art_stack *stack, struct s_art_operand *operand)
{
    stack->size++;
    stack->elements = realloc(stack->elements,
                              stack->size * sizeof (struct s_art_operand *));
    stack->elements[stack->size - 1] = operand;
}

struct s_art_operand *pop_stack(struct s_art_stack *stack)
{
    if (stack->size <= 0)
        return NULL;
    struct s_art_operand *pop = stack->elements[stack->size - 1];
    stack->size--;
    stack->elements = realloc(stack->elements,
                              stack->size * sizeof (struct s_art_operand *));
    return pop;
}

struct s_art_operand *peek_stack(struct s_art_stack *stack)
{
    if (stack->size <= 0)
        return NULL;
    struct s_art_operand *peek = stack->elements[stack->size - 1];
    return peek;
}
