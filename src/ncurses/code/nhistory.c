/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** function for history
*/

#include "../include/ncurses_fun.h"

static int find_current(char *history)
{
    int i = 0;

    if (history[0] == ' ')
        return 0;
    for (; history[i]; i++) {
        if (strncmp(history + i, "\n ", 2) == 0) {
            return i + 1;
        }
    }
    return i;
}

int nhistory_up(char *cmd)
{
    char *history = file_to_str(".history");
    int current = find_current(history);
    int start = current - 2;
    int fd = 0;

    if (current <= 0)
        return SHOW_CMD;
    for (; history[start] && history[start] != '\n'; start--);
    strncpy(cmd, history + start + 1, current - start - 2);
    delete_char(history, current);
    insert_char(history, ' ', start + 1);
    fd = open(".history", O_WRONLY | O_TRUNC);
    write(fd, history, strlen(history));
    close(fd);
    free(history);
    return SHOW_CMD;
}

int nhistory_down(char *cmd)
{
    char *history =
    file_to_str_wsize(".history", get_file_size(".history") + 2);
    int current = find_current(history);
    int start = current;
    int end = 0;
    int fd = 0;

    for (; history[start] && history[start] != '\n'; start++);
    for (end = start + 1; history[end] && history[end] != '\n'; end++);
    memset(cmd, 0, strlen(cmd));
    insert_char(history, ' ', start + 1);
    delete_char(history, current);
    fd = open(".history", O_WRONLY | O_TRUNC);
    write(fd, history, strlen(history));
    close(fd);
    strncpy(cmd, history + start + 1, end - start - 1);
    free(history);
    return SHOW_CMD;
}

int add_to_nhistory(char *cmd)
{
    FILE *file = fopen(".history", "a");

    fprintf(file, "%s\n", cmd);
    fclose(file);
    return 0;
}
