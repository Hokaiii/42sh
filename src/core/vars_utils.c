/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Shell variables management
*/

#include <stdlib.h>
#include <string.h>
#include "../../include/shell.h"

static void free_var_node(var_node_t *node)
{
    free(node->key);
    free(node->value);
    free(node);
}

static void free_var_nodes(var_node_t *head)
{
    var_node_t *current = head;
    var_node_t *next;

    while (current != NULL) {
        next = current->next;
        free_var_node(current);
        current = next;
    }
}

void free_var_list(var_list_t *list)
{
    if (list == NULL)
        return;
    free_var_nodes(list->head);
    free(list);
}
