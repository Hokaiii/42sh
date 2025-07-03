/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** main
*/

#include "../include/ncurses_fun.h"

void endwin_wrapper(void)
{
    endwin();
}

void ncurses_init(void)
{
    initscr();
    noecho();
    cbreak();
    scrollok(stdscr, TRUE);
    idlok(stdscr, TRUE);
    keypad(stdscr, TRUE);
    mouseinterval(0);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    atexit(endwin_wrapper);
}
