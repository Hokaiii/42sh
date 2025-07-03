/*
** EPITECH PROJECT, 2025
** ncurses_fun.h
** File description:
** ncurses function
*/

#include "../../../include/shell.h"
#include <unistd.h>
#include <linux/limits.h>
#include <curses.h>
#include <ncurses.h>

#ifndef NCURSES_FUN
  #define NCURSES_FUN
  #define DO_NOTHING 0
  #define NO_SIGNAL 1
  #define SHOW_CMD 2
  #define RESET_CMD 4
  #define SHOW_PROMPT 8


typedef struct loop_data_s {
    int ch;
    char cmd[1024];
    char prompt[PATH_MAX + 1];
} loop_data_t;

void ncurses_init(void);
void ncurses_loop(void);
int ncurses_signal(int ch, char *str);
int ncurses_add_char_cmd(char *cmd, int pos, char ch);

int nhistory_up(char *cmd);
int add_to_nhistory(char *cmd);
int nhistory_down(char *cmd);

int nmove_left(char *cmd);
int nmove_right(char *cmd);
int ndelete(char *cmd);
int nsuppr(char *cmd);

int display_options(char *str);
int str_to_ast(char *str);

void no_signal_action(loop_data_t *l_data);
void reset_cmd_action(loop_data_t *l_data);
void show_prompt_action(loop_data_t *l_data);
void show_cmd_action(loop_data_t *l_data);

int nmouse_handling(char *cmd);
int nscroll_down(char *cmd);
int nscroll_up(char *cmd);

#endif
