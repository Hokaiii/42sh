/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Header file
*/

#ifndef HISTORY_H
    #define HISTORY_H

    #include "types.h"

typedef struct history_entry_s {
    char *command;
    int index;
    struct history_entry_s *next;
    struct history_entry_s *prev;
} history_entry_t;

typedef struct history_s {
    history_entry_t *head;
    history_entry_t *tail;
    history_entry_t *current;
    int size;
    int max_size;
} history_t;

history_t *init_history(void);
void add_to_history(history_t *history, const char *command);
char *get_previous_command(history_t *history);
char *get_next_command(history_t *history);
void save_history(history_t *history);
void load_history(history_t *history);
void free_history(history_t *history);

#endif
