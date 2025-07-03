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

history_t *init_history(void)
{
    history_t *history = malloc(sizeof(history_t));

    if (history == NULL)
        return NULL;
    history->head = NULL;
    history->tail = NULL;
    history->current = NULL;
    history->size = 0;
    history->max_size = 1000;
    return history;
}

char *get_previous_command(history_t *history)
{
    if (history == NULL || history->head == NULL)
        return NULL;
    if (history->current == NULL)
        history->current = history->tail;
    else if (history->current->prev != NULL)
        history->current = history->current->prev;
    return history->current ? history->current->command : NULL;
}

char *get_next_command(history_t *history)
{
    if (history == NULL || history->current == NULL)
        return NULL;
    history->current = history->current->next;
    return history->current ? history->current->command : NULL;
}

static void read_history_file(history_t *history, FILE *file)
{
    char line[MAX_INPUT_LENGTH];

    while (fgets(line, MAX_INPUT_LENGTH, file) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        if (line[0] != '\0')
            add_to_history(history, line);
    }
}

static char *get_history_path(void)
{
    char *home;
    static char path[MAX_PATH_LENGTH];

    home = get_env_var(get_shell_instance()->env, "HOME");
    if (home == NULL)
        return NULL;
    snprintf(path, MAX_PATH_LENGTH, "%s/%s", home, HISTORY_FILE);
    return path;
}

void load_history(history_t *history)
{
    FILE *file;
    char *path;

    if (history == NULL)
        return;
    path = get_history_path();
    if (path == NULL)
        return;
    file = fopen(path, "r");
    if (file == NULL)
        return;
    read_history_file(history, file);
    fclose(file);
}

static void free_history_entries(history_entry_t *entry)
{
    history_entry_t *next;

    while (entry != NULL) {
        next = entry->next;
        free(entry->command);
        free(entry);
        entry = next;
    }
}

void free_history(history_t *history)
{
    if (history == NULL)
        return;
    free_history_entries(history->head);
    free(history);
}
