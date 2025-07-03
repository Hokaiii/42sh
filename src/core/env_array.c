/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** env_array.c
*/

#include <stdlib.h>
#include <string.h>
#include "../../include/shell.h"

static char *create_env_string(const char *key, const char *value)
{
    int len = strlen(key) + (value ? strlen(value) : 0) + 2;
    char *env_str = malloc(len);

    if (env_str == NULL)
        return NULL;
    strcpy(env_str, key);
    strcat(env_str, "=");
    if (value)
        strcat(env_str, value);
    return env_str;
}

static void free_env_array(char **env_array, int count)
{
    for (int j = 0; j < count; j++)
        free(env_array[j]);
    free(env_array);
}

static bool fill_env_array(char **env_array, env_list_t *list)
{
    env_node_t *current = list->head;
    int i = 0;

    while (current != NULL) {
        env_array[i] = create_env_string(current->key, current->value);
        if (env_array[i] == NULL) {
            free_env_array(env_array, i);
            return false;
        }
        i++;
        current = current->next;
    }
    env_array[i] = NULL;
    return true;
}

char **env_to_array(env_list_t *list)
{
    char **env_array;

    if (list == NULL)
        return NULL;
    env_array = malloc(sizeof(char *) * (list->size + 1));
    if (env_array == NULL)
        return NULL;
    if (!fill_env_array(env_array, list))
        return NULL;
    return env_array;
}
