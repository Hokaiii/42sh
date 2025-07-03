/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** token handling
*/

#include <stdlib.h>
#include <string.h>
#include "../../include/shell.h"

token_t *get_token(token_list_t *tokens, int offset)
{
    token_t *token = tokens->head;
    int i = 0;

    while (token != NULL && i < offset) {
        token = token->next;
        i++;
    }
    return token;
}

void advance_token(token_list_t *tokens)
{
    token_t *old_head;

    if (tokens->head != NULL) {
        old_head = tokens->head;
        tokens->head = tokens->head->next;
        tokens->size--;
        free(old_head->value);
        free(old_head);
    }
}

bool expect_token(token_list_t *tokens, token_type_t type)
{
    if (tokens->head == NULL || tokens->head->type != type)
        return false;
    advance_token(tokens);
    return true;
}

char **collect_command_args(token_list_t *tokens)
{
    int arg_count = 0;
    token_t *token = tokens->head;
    char **args;

    while (token != NULL && token->type == TOKEN_WORD) {
        arg_count++;
        token = token->next;
    }
    if (arg_count == 0)
        return NULL;
    args = malloc(sizeof(char *) * (arg_count + 1));
    if (args == NULL)
        return NULL;
    for (int i = 0; i < arg_count; i++) {
        args[i] = strdup(tokens->head->value);
        advance_token(tokens);
    }
    args[arg_count] = NULL;
    handle_globbing(&args);
    return args;
}
