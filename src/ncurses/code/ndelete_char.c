/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** function to add a character
*/

#include "../include/ncurses_fun.h"

static int ncurses_delete_char_cmd(char *cmd, int offset)
{
    int x;
    int y;

    getyx(stdscr, y, x);
    if (offset < x){
        delete_char(cmd, x - offset - 1);
        mvdelch(y, x - 1);
        move(y, x - 1);
    }
    return 0;
}

int ndelete(char *cmd)
{
    char cdir[PATH_MAX];

    getcwd(cdir, sizeof(cdir));
    ncurses_delete_char_cmd(cmd, strlen(cdir) + 1);
    return SHOW_CMD;
}

int nsuppr(char *cmd)
{
    ndelete(cmd);
    return DO_NOTHING;
}
