/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** env.c
*/

#include <stdlib.h>
#include <string.h>
#include "../../include/shell.h"

env_list_t *init_env_list(void)
{
    env_list_t *list = malloc(sizeof(env_list_t));

    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->size = 0;
    return list;
}

static bool update_existing_env_var(env_list_t *list, const char *key,
    const char *value)
{
    env_node_t *current = list->head;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = value ? strdup(value) : NULL;
            return true;
        }
        current = current->next;
    }
    return false;
}

static void create_new_env_var(env_list_t *list, const char *key,
    const char *value)
{
    env_node_t *node = malloc(sizeof(env_node_t));

    if (node == NULL)
        return;
    node->key = strdup(key);
    node->value = value ? strdup(value) : NULL;
    node->next = list->head;
    list->head = node;
    list->size++;
}

void add_env_var(env_list_t *list, const char *key, const char *value)
{
    if (list == NULL || key == NULL)
        return;
    if (!update_existing_env_var(list, key, value))
        create_new_env_var(list, key, value);
}

static void free_env_node(env_node_t *node)
{
    free(node->key);
    free(node->value);
    free(node);
}

static void update_env_list_pointers(env_list_t *list, env_node_t *prev,
    env_node_t *current)
{
    if (prev == NULL)
        list->head = current->next;
    else
        prev->next = current->next;
}

void remove_env_var(env_list_t *list, const char *key)
{
    env_node_t *current;
    env_node_t *prev = NULL;

    if (list == NULL || key == NULL || list->head == NULL)
        return;
    current = list->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            update_env_list_pointers(list, prev, current);
            free_env_node(current);
            list->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

char *get_env_var(env_list_t *list, const char *key)
{
    env_node_t *current;

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

void free_env_list(env_list_t *list)
{
    env_node_t *current;
    env_node_t *next;

    if (list == NULL)
        return;
    current = list->head;
    while (current != NULL) {
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
    free(list);
}
