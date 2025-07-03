/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** add_alias
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../../../include/shell.h"
#include "../../../include/alias.h"

static int free_nodes(alias_node_t *new_node)
{
    if (!new_node->name || !new_node->value) {
        free(new_node->name);
        free(new_node->value);
        free(new_node);
        return 1;
    }
    return 0;
}

static int check_alias_existence(alias_list_t *list, const char *name,
    const char *value)
{
    alias_node_t *current = list->head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            free(current->value);
            current->value = strdup(value);
            return 0;
        }
        current = current->next;
    }
    return 1;
}

int add_alias(alias_list_t *list, const char *name, const char *value)
{
    alias_node_t *new_node = NULL;

    if (!list || !name || !value)
        return 1;
    if (check_alias_existence(list, name, value) == 0)
        return 0;
    new_node = malloc(sizeof(alias_node_t));
    if (!new_node)
        return 1;
    new_node->name = strdup(name);
    new_node->value = strdup(value);
    if (free_nodes(new_node) == 1)
        return 1;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    return 0;
}
