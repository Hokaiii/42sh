/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Shell signal handling
*/

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "../../include/shell.h"

static void handle_sigint(shell_data_t *shell)
{
    if (shell && shell->current_pid > 0) {
        kill(shell->current_pid, SIGINT);
        shell->exit_code = 130;
    } else {
        write(STDOUT_FILENO, "\n", 1);
        if (shell && shell->term)
            display_prompt();
    }
}

static void signal_handler(int signum)
{
    shell_data_t *shell = get_shell_instance();

    if (signum == SIGINT)
        handle_sigint(shell);
}

void handle_signals(void)
{
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}
