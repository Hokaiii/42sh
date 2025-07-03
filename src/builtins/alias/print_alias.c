/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** print_alias
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../../../include/shell.h"
#include "../../../include/alias.h"

void print_alias_list(alias_list_t *list)
{
    alias_node_t *tmp = list->head;

    while (tmp) {
        fprintf(stdout, "alias %s=%s\n", tmp->name, tmp->value);
        tmp = tmp->next;
    }
}
