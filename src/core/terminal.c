/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** terminal.c
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "../../include/shell.h"

terminal_t *init_terminal(void)
{
    terminal_t *term = malloc(sizeof(terminal_t));

    if (term == NULL)
        return NULL;
    tcgetattr(STDIN_FILENO, &term->original);
    term->current = term->original;
    memset(term->buffer, 0, MAX_INPUT_LENGTH);
    term->cursor_pos = 0;
    term->buffer_len = 0;
    term->cursor_row = 0;
    term->cursor_col = 0;
    term->raw_mode = false;
    return term;
}

void enable_raw_mode(terminal_t *term)
{
    if (term == NULL || !isatty(STDIN_FILENO) || term->raw_mode)
        return;
    tcgetattr(STDIN_FILENO, &term->current);
    term->current.c_lflag &= ~(ICANON | ECHO | ISIG);
    term->current.c_cc[VMIN] = 1;
    term->current.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->current);
    term->raw_mode = true;
}

void disable_raw_mode(terminal_t *term)
{
    if (term == NULL || !isatty(STDIN_FILENO) || !term->raw_mode)
        return;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->original);
    term->raw_mode = false;
}

static char *read_from_pipe(void)
{
    char *line = NULL;
    size_t size = 0;

    if (getline(&line, &size, stdin) == -1) {
        free(line);
        return NULL;
    }
    line[strcspn(line, "\n")] = '\0';
    return line;
}

static void init_term_buffer(terminal_t *term)
{
    memset(term->buffer, 0, MAX_INPUT_LENGTH);
    term->buffer_len = 0;
    term->cursor_pos = 0;
}

static char *handle_ctrl_d(terminal_t *term)
{
    disable_raw_mode(term);
    write(STDOUT_FILENO, "exit\n", 5);
    return NULL;
}

char *read_line_raw(terminal_t *term)
{
    char c;
    char *line;

    if (!isatty(STDIN_FILENO))
        return read_from_pipe();
    init_term_buffer(term);
    enable_raw_mode(term);
    while (1) {
        if (read(STDIN_FILENO, &c, 1) <= 0)
            break;
        if (c == ENTER) {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
        if (c == CTRL_D && term->buffer_len == 0)
            return handle_ctrl_d(term);
        handle_key(term, c);
    }
    disable_raw_mode(term);
    return strdup(term->buffer);
}

void free_terminal(terminal_t *term)
{
    if (term == NULL)
        return;
    disable_raw_mode(term);
    free(term);
}
