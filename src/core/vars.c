/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Shell variables management
*/

#include <stdlib.h>
#include <string.h>
#include "../../include/shell.h"

var_list_t *init_var_list(void)
{
    var_list_t *list = malloc(sizeof(var_list_t));

    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->size = 0;
    return list;
}

static var_node_t *create_var_node(const char *key, const char *value,
    bool readonly)
{
    var_node_t *node = malloc(sizeof(var_node_t));

    if (node == NULL)
        return NULL;
    node->key = strdup(key);
    if (node->key == NULL) {
        free(node);
        return NULL;
    }
    node->value = value ? strdup(value) : NULL;
    if (value != NULL && node->value == NULL) {
        free(node->key);
        free(node);
        return NULL;
    }
    node->readonly = readonly;
    node->next = NULL;
    return node;
}

static int update_existing_var(var_node_t *current, const char *value,
    bool readonly)
{
    if (current->readonly)
        return 1;
    free(current->value);
    current->value = value ? strdup(value) : NULL;
    current->readonly = readonly;
    return 1;
}

static var_node_t *find_var_node(var_list_t *list, const char *key)
{
    var_node_t *current = list->head;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

void add_var(var_list_t *list, const char *key, const char *value,
    bool readonly)
{
    var_node_t *node;
    var_node_t *existing;

    if (list == NULL || key == NULL)
        return;
    existing = find_var_node(list, key);
    if (existing != NULL && update_existing_var(existing, value, readonly))
        return;
    node = create_var_node(key, value, readonly);
    if (node == NULL)
        return;
    node->next = list->head;
    list->head = node;
    list->size++;
}

void free_var_node(var_node_t *node)
{
    free(node->key);
    free(node->value);
    free(node);
}

static void remove_node_from_list(var_list_t *list, var_node_t *current,
    var_node_t *prev)
{
    if (prev == NULL)
        list->head = current->next;
    else
        prev->next = current->next;
    free_var_node(current);
    list->size--;
}

static bool can_remove_var(var_node_t *node)
{
    return !node->readonly;
}

void remove_var(var_list_t *list, const char *key)
{
    var_node_t *current;
    var_node_t *prev = NULL;

    if (list == NULL || key == NULL || list->head == NULL)
        return;
    current = list->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0 && can_remove_var(current)) {
            remove_node_from_list(list, current, prev);
            return;
        }
        prev = current;
        current = current->next;
    }
}

char *get_var(var_list_t *list, const char *key)
{
    var_node_t *current;

    if (list == NULL || key == NULL)
        return NULL;
    current = list->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}
