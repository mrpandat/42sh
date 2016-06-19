#define _GNU_SOURCE

#include <arith_lexer.h>
#include <expansion.h>
#include "../includes/global.h"
#include "../includes/expansion.h"
#include "../includes/util.h"

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
