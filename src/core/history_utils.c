/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** history.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../../include/shell.h"

static void remove_oldest_entry(history_t *history)
{
    history_entry_t *entry = history->head;

    history->head = entry->next;
    if (history->head != NULL)
        history->head->prev = NULL;
    free(entry->command);
    free(entry);
    history->size--;
}

static history_entry_t *create_history_entry(history_t *history,
    const char *command)
{
    history_entry_t *entry = malloc(sizeof(history_entry_t));

    if (entry == NULL)
        return NULL;
    entry->command = strdup(command);
    entry->index = history->size;
    entry->next = NULL;
    entry->prev = history->tail;
    return entry;
}

static void add_entry_to_list(history_t *history, history_entry_t *entry)
{
    if (history->tail != NULL)
        history->tail->next = entry;
    else
        history->head = entry;
    history->tail = entry;
    history->current = NULL;
    history->size++;
}

void add_to_history(history_t *history, const char *command)
{
    history_entry_t *entry;

    if (history == NULL || command == NULL || command[0] == '\0')
        return;
    entry = create_history_entry(history, command);
    if (entry == NULL)
        return;
    add_entry_to_list(history, entry);
    if (history->size > history->max_size)
        remove_oldest_entry(history);
}

void save_history(history_t *history)
{
    FILE *file;
    history_entry_t *entry;
    char *home;
    char path[MAX_PATH_LENGTH];

    if (history == NULL || history->head == NULL)
        return;
    home = get_env_var(get_shell_instance()->env, "HOME");
    if (home == NULL)
        return;
    snprintf(path, MAX_PATH_LENGTH, "%s/%s", home, HISTORY_FILE);
    file = fopen(path, "w");
    if (file == NULL)
        return;
    entry = history->head;
    while (entry != NULL) {
        fprintf(file, "%s\n", entry->command);
        entry = entry->next;
    }
    fclose(file);
}
