/*
** EPITECH PROJECT, 2025
** ncurses_mouse.h
** File description:
** function pointer for mouse related signals
*/

#include "ncurses_fun.h"

#ifndef NCURSES_SIGNAL
  #define NCURSES_SIGNAL
typedef struct s_mouse_fptr {
    int sign;
    int (*fptr)(char *str);
} mouse_fptr_t;

const mouse_fptr_t NMOUSE[] = {
    {BUTTON4_PRESSED, &nscroll_up},
    {BUTTON5_PRESSED, &nscroll_down},
    {0, NULL}
};

#endif
