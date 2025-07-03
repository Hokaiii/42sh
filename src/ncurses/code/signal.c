/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** launch n curses process
*/

#include "../include/ncurses_fun.h"
#include "../include/ncurses_signals.h"

int ncurses_signal(int ch, char *cmd)
{
    for (int i = 0; NSIGNAL[i].fptr; i++){
        if (NSIGNAL[i].ch == ch)
            return NSIGNAL[i].fptr(cmd);
    }
    return NO_SIGNAL;
}
