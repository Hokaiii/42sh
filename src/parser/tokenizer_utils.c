/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** tokenizer
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../../include/shell.h"

void add_token(token_list_t *list, token_type_t type, char *value)
{
    token_t *token;

    if (list == NULL)
        return;
    token = malloc(sizeof(token_t));
    if (token == NULL)
        return;
    token->type = type;
    token->value = value ? strdup(value) : NULL;
    token->next = NULL;
    if (list->head == NULL) {
        list->head = token;
        list->current = token;
    } else {
        list->current->next = token;
        list->current = token;
    }
    list->size++;
}

void free_token_list(token_list_t *list)
{
    token_t *token;
    token_t *next;

    if (list == NULL)
        return;
    token = list->head;
    while (token != NULL) {
        next = token->next;
        free(token->value);
        free(token);
        token = next;
    }
    free(list);
}

token_list_t *init_token_list(void)
{
    token_list_t *list = malloc(sizeof(token_list_t));

    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->current = NULL;
    list->size = 0;
    return list;
}
