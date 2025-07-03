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

static void handle_backspace(terminal_t *term)
{
    int i;

    if (term->cursor_pos <= 0)
        return;
    write(STDOUT_FILENO, "\b", 1);
    memmove(&term->buffer[term->cursor_pos - 1],
            &term->buffer[term->cursor_pos],
            term->buffer_len - term->cursor_pos);
    term->cursor_pos--;
    term->buffer_len--;
    term->buffer[term->buffer_len] = '\0';
    write(STDOUT_FILENO, &term->buffer[term->cursor_pos],
        term->buffer_len - term->cursor_pos);
    write(STDOUT_FILENO, " ", 1);
    for (i = 0; i <= term->buffer_len - term->cursor_pos; i++) {
        write(STDOUT_FILENO, "\b", 1);
    }
}

static void handle_printable_char(terminal_t *term, int key)
{
    if (term->buffer_len >= MAX_INPUT_LENGTH - 1)
        return;
    if (term->cursor_pos < term->buffer_len) {
        memmove(&term->buffer[term->cursor_pos + 1],
                &term->buffer[term->cursor_pos],
                term->buffer_len - term->cursor_pos);
    }
    term->buffer[term->cursor_pos] = key;
    write(STDOUT_FILENO, &key, 1);
    term->cursor_pos++;
    term->buffer_len++;
    term->buffer[term->buffer_len] = '\0';
    if (term->cursor_pos < term->buffer_len)
        refresh_line(term);
}

static void handle_navigation_keys(terminal_t *term, int key)
{
    switch (key) {
        case CTRL_A:
            while (term->cursor_pos > 0)
                move_cursor_left(term);
            break;
        case CTRL_E:
            while (term->cursor_pos < term->buffer_len)
                move_cursor_right(term);
            break;
        case '\t':
            handle_tab_completion(term);
            break;
    }
}

static void handle_editing_keys(terminal_t *term, int key, shell_data_t *sh)
{
    if (key == BACKSPACE) {
        handle_backspace(term);
        return;
    }
    if (key == ESCAPE) {
        handle_escape_sequence(term, sh);
        return;
    }
    if (key >= 32 && key < 127) {
        handle_printable_char(term, key);
    }
}

static bool is_navigation_key(int key)
{
    return (key == CTRL_A || key == CTRL_E || key == '\t');
}

void handle_key(terminal_t *term, int key)
{
    shell_data_t *sh = get_shell_instance();

    if (is_navigation_key(key)) {
        handle_navigation_keys(term, key);
        return;
    }
    handle_editing_keys(term, key, sh);
}
