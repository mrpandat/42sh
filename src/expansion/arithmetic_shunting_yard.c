#define _GNU_SOURCE

#include <arith_lexer.h>
#include <expansion.h>
#include "../includes/global.h"
#include "../includes/expansion.h"
#include "../includes/util.h"

static struct s_art_operand *init_token_operand(struct s_arlex_token *token)
{
    struct s_art_operand *operand = malloc(sizeof(struct s_art_operand));
    operand->type = OPERAND_TOKEN;
    operand->data.token = token;
    return operand;
}

static struct s_art_operand *init_node_operand(struct s_art_node *node)
{
    struct s_art_operand *operand = malloc(sizeof(struct s_art_operand));
    operand->type = OPERAND_NODE;
    operand->data.node = node;
    return operand;
}

static void reduct(struct s_art_stack *operands,
                   struct s_art_stack *operators)
{
    struct s_art_node *node = init_art_node();
    struct s_art_operand * operator = pop_stack(operators);
    enum e_arlex_type type = operator->data.token->type;
    if (type == AL_UNARY_MINUS || type == AL_UNARY_PLUS
        || type == AL_BW_NEG || type == AL_LG_NEG)
    {
        struct s_art_operand *operand = pop_stack(operands);
        struct s_unop_node *unop = init_unop_node(type, operand->data.node);
        free(operand);
        node->type = ART_UNOP;
        node->data.unop = unop;
    }
    else
    {
        struct s_art_operand *right = pop_stack(operands);
        struct s_art_operand *left = pop_stack(operands);
        struct s_binop_node *binop = init_binop_node(left->data.node,
                                                     type,
                                                     right->data.node);
        free(right);
        free(left);
        node->type = ART_BINOP;
        node->data.binop = binop;
    }
    free(operator);
    add_stack(operands, init_node_operand(node));
}

struct s_art_node *shunting_yard(struct s_arlex *lexer)
{
    bool op_previous = true;
    struct s_art_stack *operands = init_stack();
    struct s_art_stack *operators = init_stack();
    struct s_arlex_token *token = arlex_peek(lexer);
    while (token->type != AL_EOF && token->type != AL_NEWLINE
           && token->type != AL_UNDEFINED)
    {
        if (token->type == AL_VAR || token->type == AL_NUMBER)
        {
            struct s_number_node *number;
            if (token->type == AL_VAR)
                number = init_num_node_var(token->value);
            else
                number = init_num_node_int(atoi(token->value));
            struct s_art_node *node = init_art_node();
            node->type = ART_NUM;
            node->data.number = number;
            struct s_art_operand *operand = init_node_operand(node);
            add_stack(operands, operand);
            token = arlex_read(lexer);
            op_previous = false;

        }
        else if (token->type == AL_RPAR)
        {
            while (peek_stack(operators) != NULL
                   && peek_stack(operators)->data.token->type != AL_LPAR)
            {
                reduct(operands, operators);
                op_previous = false;
            }
            if (peek_stack(operators)->data.token->type == AL_LPAR)
                free(pop_stack(operators));
            token = arlex_read(lexer);
            op_previous = false;
        }
        else
        {
            struct s_art_operand *operator = peek_stack(operators);
            if (operator == NULL
                || token->type == AL_LPAR
                || operator->data.token->type <= token->type
                || (token->type == AL_PLUS && op_previous)
                || (token->type == AL_MINUS && op_previous))
            {
                if (op_previous)
                {
                    if (token->type == AL_PLUS)
                        token->type = AL_UNARY_PLUS;
                    else if (token->type == AL_MINUS)
                        token->type = AL_UNARY_MINUS;
                }
                add_stack(operators, init_token_operand(token));
                token = arlex_read(lexer);
                op_previous = true;
            }
            else
            {
                reduct(operands, operators);
                op_previous = false;
            }
        }
    }
    if (token->type == AL_NEWLINE || token->type == AL_UNDEFINED)
    {
        free_stack(operands);
        free_stack(operators);
        return NULL;
    }
    while (peek_stack(operators) != NULL)
        reduct(operands, operators);
    struct s_art_node *root = peek_stack(operands)->data.node;
    free_stack(operands);
    free_stack(operators);
    return root;
}
