/*
** EPITECH PROJECT, 2025
** nmouse_handling
** File description:
** function pointer pick function
*/

#include "../include/ncurses_fun.h"
#include "../include/ncurses_mouse.h"

int nmouse_handling(char *cmd)
{
    MEVENT event;

    if (!(getmouse(&event) == OK))
        return NO_SIGNAL;
    for (int i = 0; NMOUSE[i].fptr; i++){
        if (event.bstate & NMOUSE[i].sign){
            return NMOUSE[i].fptr(cmd);
        }
    }
    return NO_SIGNAL;
}
