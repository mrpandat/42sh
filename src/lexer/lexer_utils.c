#include "../includes/lexer.h"

void print_lexer(struct s_lexer *lexer)
{
    char *command = lexer->command;
    int position = lexer_current_position(lexer);

    fprintf(stdout, "\n[LEXER]\ncommand: %s\nposition: %d\n", command,
            position);

    print_token(lexer->tk_list);

    fprintf(stdout, "\n");
}

void print_token_list(struct s_lexer *lexer)
{
    size_t len = 0;
    fprintf(stdout, "token list:\n");

    if (NULL == lexer || NULL == lexer->tk_list)
    {
        fprintf(stdout, "[EMPTY]\n");
        return;
    }

    struct s_lexer_token *list = lexer->tk_list;
    while (NULL != list)
    {
        print_token(list);
        len++;
        if (NULL != list->next)
        {
            fprintf(stdout, " -> ");
        }
        if (4 == len)
        {
            fprintf(stdout, "\n");
            len = 0;
        }
        list = list->next;
    }
}

void print_token(struct s_lexer_token *token)
{
    if (NULL == token)
    {
        fprintf(stdout, "No token_list.\n");
        return;
    }

    char *type;
    char *value = token->value;

    switch (token->type)
    {
        case TK_IF:
            type = "TK_IF";
            break;
        case TK_THEN:
            type = "TK_THEN";
            break;
        case TK_ELIF:
            type = "TK_ELIF";
            break;
        case TK_ELSE:
            type = "TK_ELSE";
            break;
        case TK_FI:
            type = "TK_FI";
            break;
        case TK_WORD:
            type = "TK_WORD";
            break;
        case TK_DO:
            type = "TK_DO";
            break;
        case TK_DONE:
            type = "TK_DONE";
            break;
        case TK_CASE:
            type = "TK_CASE";
            break;
        case TK_ESAC:
            type = "TK_ESAC";
            break;
        case TK_WHILE:
            type = "TK_WHILE";
            break;
        case TK_UNTIL:
            type = "TK_UNTIL";
            break;
        case TK_FOR:
            type = "TK_FOR";
            break;
        case TK_IN:
            type = "TK_IN";
            break;
        case TK_AND:
            type = "TK_AND";
            break;
        case TK_OR:
            type = "TK_OR";
            break;
        case TK_AND_IF:
            type = "TK_AND_IF";
            break;
        case TK_OR_IF:
            type = "TK_OR_IF";
            break;
        case TK_SEMI:
            type = "TK_SEMI";
            break;
        case TK_DSEMI:
            type = "TK_DSEMI";
            break;
        case TK_EOF:
            type = "TK_EOF";
            break;
        case TK_UNDEFINED:
            type = "TK_UNDEFINED";
            break;
        default:
            type = "NULL";
            break;
    }

    fprintf(stdout, "[%s : %s]", type, value);
}
