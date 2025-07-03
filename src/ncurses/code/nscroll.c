/*
** EPITECH PROJECT, 2025
** nscroll
** File description:
** function to scroll
*/

#include "../include/ncurses.h"

int nscroll_up(char *cmd)
{
    if (cmd)
        scrl(-1);
    return 0;
}

int nscroll_down(char *cmd)
{
    if (cmd)
        scrl(1);
    return 0;
}
