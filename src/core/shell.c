/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Main shell functions
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../include/shell.h"

static void init_shell_data(shell_data_t *shell)
{
    shell->env = NULL;
    shell->vars = NULL;
    shell->aliases = NULL;
    shell->input_buffer = NULL;
    shell->current_dir = NULL;
    shell->previous_dir = NULL;
    shell->home_dir = NULL;
    shell->exit_code = 0;
    shell->should_exit = false;
    shell->current_pid = 0;
    shell->saved_stdin = -1;
    shell->saved_stdout = -1;
    shell->term = NULL;
    shell->history = NULL;
}

shell_data_t *get_shell_instance(void)
{
    static shell_data_t *shell;

    if (shell == NULL) {
        shell = malloc(sizeof(shell_data_t));
        if (shell == NULL)
            return NULL;
        init_shell_data(shell);
    }
    return shell;
}

static bool handle_empty_input(shell_data_t *sh, char *input)
{
    if (input == NULL) {
        sh->should_exit = true;
        return true;
    }
    if (input[0] == '\0') {
        free(input);
        return true;
    }
    return false;
}

int run_shell_loop(void)
{
    shell_data_t *sh = get_shell_instance();
    char *input;

    while (!sh->should_exit) {
        display_prompt();
        input = read_input();
        if (handle_empty_input(sh, input))
            continue;
        sh->exit_code = process_input(sh, input);
        free(input);
    }
    return SUCCESS;
}
