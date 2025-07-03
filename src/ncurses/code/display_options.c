/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** main
*/

#include "../include/ncurses_fun.h"

char **environ;

static char **get_binairies(char **path, char *cmd)
{
    return NULL;
}

static void display_file_options(char *cmd)
{
    printw("display file\n");
}

static void display_cmd_options(char **path, char *cmd)
{
    printw("display_commands\n");
}

int display_options(char *cmd)
{
    char *path[] = { "/bin", "/usr/bin", NULL };
    char pure_cmd[strcspn(cmd, " ") + 1];

    sscanf(cmd, "%s", pure_cmd);
    printw("%s\n", pure_cmd);
    if (is_a_bin(path, pure_cmd))
        display_file_options(cmd);
    else
        display_cmd_options(path, cmd);
    return SHOW_PROMPT + SHOW_CMD;
}
