/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** free_alias
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../../../include/shell.h"
#include "../../../include/alias.h"

void free_alias_list(alias_list_t *list)
{
    alias_node_t *current = list->head;
    alias_node_t *next;

    while (current != NULL) {
        next = current->next;
        free(current->name);
        free(current->value);
        free(current);
        current = next;
    }
    free(list);
}
