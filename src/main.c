/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** main.c
*/

#include "../include/shell.h"

int main(int ac, char **argv, char **envp)
{
    if (initialize_shell(envp) != SUCCESS)
        return ERROR;
    if (ac == 2 && strcmp(argv[1], "-n") == 0)
        ncurses_process();
    else
        run_shell_loop();
    return cleanup_shell();
}
