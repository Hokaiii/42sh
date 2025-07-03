/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** function to add a character
*/

#include "../include/ncurses_fun.h"

int ncurses_add_char_cmd(char *cmd, int offset, char ch)
{
    int x;
    int y;

    getyx(stdscr, y, x);
    insert_char(cmd, ch, x - offset);
    mvprintw(y, offset, "%s", cmd);
    move(y, x + 1);
    return SHOW_PROMPT + SHOW_CMD;
}
