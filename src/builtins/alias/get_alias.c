/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** get_alias
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../../../include/shell.h"
#include "../../../include/alias.h"

const char *get_alias(alias_list_t *list, const char *key)
{
    alias_node_t *current = NULL;

    if (!list || !key)
        return NULL;
    current = list->head;
    while (current != NULL) {
        if (strcmp(current->name, key) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}
