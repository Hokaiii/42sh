/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Header file
*/

#ifndef TERMINAL_H
    #define TERMINAL_H

    #include <termios.h>
    #include "types.h"

typedef struct terminal_s {
    struct termios original;
    struct termios current;
    char buffer[MAX_INPUT_LENGTH];
    int cursor_pos;
    int buffer_len;
    int cursor_row;
    int cursor_col;
    bool raw_mode;
} terminal_t;

terminal_t *init_terminal(void);
void enable_raw_mode(terminal_t *term);
void disable_raw_mode(terminal_t *term);
char *read_line_raw(terminal_t *term);
void handle_key(terminal_t *term, int key);
void move_cursor_left(terminal_t *term);
void move_cursor_right(terminal_t *term);
void clear_line(terminal_t *term);
void refresh_line(terminal_t *term);
void get_cursor_position(int *row, int *col);
void set_cursor_position(int row, int col);
void free_terminal(terminal_t *term);

#endif
