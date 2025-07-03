/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** terminal_input.c
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "../../include/shell.h"

static void handle_history_command(terminal_t *term, char *history_cmd)
{
    if (history_cmd == NULL)
        return;
    strncpy(term->buffer, history_cmd, MAX_INPUT_LENGTH - 1);
    term->buffer_len = strlen(term->buffer);
    term->cursor_pos = term->buffer_len;
    clear_line(term);
    display_prompt();
    write(STDOUT_FILENO, term->buffer, term->buffer_len);
}

static void handle_empty_history(terminal_t *term)
{
    term->buffer[0] = '\0';
    term->buffer_len = 0;
    term->cursor_pos = 0;
    clear_line(term);
    display_prompt();
}

static void handle_arrow_up(terminal_t *term, shell_data_t *sh)
{
    char *history_cmd = get_previous_command(sh->history);

    handle_history_command(term, history_cmd);
}

static void handle_arrow_down(terminal_t *term, shell_data_t *sh)
{
    char *history_cmd = get_next_command(sh->history);

    if (history_cmd != NULL)
        handle_history_command(term, history_cmd);
    else
        handle_empty_history(term);
}

static void handle_arrow_up_down(terminal_t *term, shell_data_t *sh,
    char direction)
{
    switch (direction) {
        case 'A':
            handle_arrow_up(term, sh);
            break;
        case 'B':
            handle_arrow_down(term, sh);
            break;
        case 'C':
            move_cursor_right(term);
            break;
        case 'D':
            move_cursor_left(term);
            break;
    }
}

void handle_escape_sequence(terminal_t *term, shell_data_t *sh)
{
    char seq[3];

    if (read(STDIN_FILENO, seq, 1) == -1)
        return;
    if (read(STDIN_FILENO, seq + 1, 1) == -1)
        return;
    if (seq[0] != '[')
        return;
    handle_arrow_up_down(term, sh, seq[1]);
}
