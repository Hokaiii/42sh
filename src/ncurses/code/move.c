/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** main
*/

#include "../include/ncurses_fun.h"

static void move_cursor_horizontaly(int offset, char *cmd)
{
    size_t x;
    size_t y;
    char cdir[PATH_MAX];

    getyx(stdscr, y, x);
    getcwd(cdir, sizeof(cdir));
    while (x + offset < strlen(cdir) + 1)
        offset += 1;
    while (cmd && x + offset > strlen(cdir) + 1 + strlen(cmd))
        offset -= 1;
    move(y, x + offset);
}

int nmove_left(char *cmd)
{
    move_cursor_horizontaly(-1, cmd);
    return DO_NOTHING;
}

int nmove_right(char *cmd)
{
    move_cursor_horizontaly(1, cmd);
    return DO_NOTHING;
}
