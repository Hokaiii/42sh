/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** main
*/

#include "../include/ncurses_fun.h"
#include "../include/ncurses_actions.h"

void no_signal_action(loop_data_t *l_data)
{
    ncurses_add_char_cmd(l_data->cmd, strlen(l_data->prompt), l_data->ch);
}

void reset_cmd_action(loop_data_t *l_data)
{
    memset(l_data->cmd, 0, sizeof(l_data->cmd));
}

void show_prompt_action(loop_data_t *l_data)
{
    getcwd(l_data->prompt, sizeof(l_data->prompt));
    strcat(l_data->prompt, "$");
    printw("%s", l_data->prompt);
}

void show_cmd_action(loop_data_t *l_data)
{
    int yx[2];

    getyx(stdscr, yx[0], yx[1]);
    mvprintw(yx[0], strlen(l_data->prompt),
    "                                                                      ");
    mvprintw(yx[0], strlen(l_data->prompt), "%s", l_data->cmd);
    move(yx[0], yx[1]);
}

static void trigger_action(loop_data_t *l_data, int action)
{
    for (int i = 0; ACTIONS[i].fptr; i++){
        if (action >= ACTIONS[i].action){
            ACTIONS[i].fptr(l_data);
            trigger_action(l_data, action - ACTIONS[i].action);
            return;
        }
    }
}

void ncurses_loop()
{
    int mode = 0;
    loop_data_t l_data = {0, {0}, {0}};

    show_prompt_action(&l_data);
    while (1){
        l_data.ch = getch();
        mode = ncurses_signal(l_data.ch, l_data.cmd);
        trigger_action(&l_data, mode);
        refresh();
    }
}
