/*
** EPITECH PROJECT, 2025
** ncurses signals
** File description:
** function pointer for signals
*/

#include "ncurses_fun.h"

#ifndef NCURSES_SIGNAL
  #define NCURSES_SIGNAL

typedef struct s_actions_fptr {
    int action;
    void (*fptr)(loop_data_t *loop_data);
} s_actions_t;

const s_actions_t ACTIONS[] = {
    {SHOW_PROMPT, &show_prompt_action},
    {RESET_CMD, &reset_cmd_action},
    {SHOW_CMD, &show_cmd_action},
    {NO_SIGNAL, &no_signal_action},
    {DO_NOTHING, NULL}
};

// It's important that they are in the degressive order
#endif
