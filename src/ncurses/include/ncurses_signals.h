/*
** EPITECH PROJECT, 2025
** ncurses signals
** File description:
** function pointer for signals
*/

#include "ncurses_fun.h"

#ifndef NCURSES_SIGNAL
  #define NCURSES_SIGNAL
typedef struct s_signal_fptr {
    int ch;
    int (*fptr)(char *str);
} s_signal_fptr_with_arg_t;

const struct s_signal_fptr NSIGNAL[] = {
    {KEY_UP, &nhistory_up},
    {KEY_DOWN, &nhistory_down},
    {'\n', &str_to_ast},
    {'\t', &display_options},
    {KEY_LEFT, &nmove_left},
    {KEY_RIGHT, &nmove_right},
    {KEY_BACKSPACE, &ndelete},
    {KEY_DC, &nsuppr},
    {KEY_MOUSE, &nmouse_handling},
    {0, NULL}
};

#endif
