/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** launch n curses process
*/

#include "../include/ncurses_fun.h"

void ncurses_process(void)
{
    ncurses_init();
    ncurses_loop();
    endwin();
}
