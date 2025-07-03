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

void handle_tab_completion(terminal_t *term)
{
    (void)term;
    write(STDOUT_FILENO, "\a", 1);
}

void move_cursor_left(terminal_t *term)
{
    if (term->cursor_pos > 0) {
        term->cursor_pos--;
        write(STDOUT_FILENO, "\b", 1);
    }
}

static void increment_cursor_position(terminal_t *term)
{
    term->cursor_pos++;
}

void move_cursor_right(terminal_t *term)
{
    if (term->cursor_pos < term->buffer_len) {
        write(STDOUT_FILENO, "\033[1C", 4);
        increment_cursor_position(term);
    }
}
