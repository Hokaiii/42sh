/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** terminal cursor
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "../../include/shell.h"

void get_cursor_position(int *row, int *col)
{
    char buf[32];
    unsigned int i = 0;

    if (!isatty(STDIN_FILENO))
        return;
    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
        return;
    while (i < sizeof(buf) - 1) {
        if (read(STDIN_FILENO, buf + i, 1) != 1)
            break;
        if (buf[i] == 'R')
            break;
        i++;
    }
    buf[i] = '\0';
    if (buf[0] != '\x1b' || buf[1] != '[')
        return;
    if (sscanf(buf + 2, "%d;%d", row, col) != 2)
        return;
}

void set_cursor_position(int row, int col)
{
    char buf[32];
    int len;

    if (!isatty(STDOUT_FILENO))
        return;
    len = snprintf(buf, sizeof(buf), "\x1b[%d;%dH", row, col);
    write(STDOUT_FILENO, buf, len);
}

void clear_line(terminal_t *term)
{
    if (!isatty(STDOUT_FILENO))
        return;
    write(STDOUT_FILENO, "\r\x1b[K", 4);
    term->cursor_pos = 0;
}

void refresh_line(terminal_t *term)
{
    int i;

    if (!isatty(STDOUT_FILENO))
        return;
    clear_line(term);
    display_prompt();
    write(STDOUT_FILENO, term->buffer, term->buffer_len);
    if (term->cursor_pos < term->buffer_len) {
        for (i = 0; i < term->buffer_len - term->cursor_pos; i++)
            write(STDOUT_FILENO, "\b", 1);
    }
}
