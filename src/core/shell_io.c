/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Shell input/output functions
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../../include/shell.h"

static char *create_home_path(const char *cwd, const char *home)
{
    char *display_path;

    if (home == NULL || strncmp(cwd, home, strlen(home)) != 0)
        return NULL;
    display_path = malloc(strlen(cwd) - strlen(home) + 2);
    if (display_path == NULL)
        return NULL;
    display_path[0] = '~';
    strcpy(display_path + 1, cwd + strlen(home));
    return display_path;
}

void display_prompt(void)
{
    shell_data_t *sh = get_shell_instance();
    char *cwd = sh->current_dir;
    char *home = sh->home_dir;
    char *display_path = cwd;
    char *home_path = NULL;

    if (home != NULL)
        home_path = create_home_path(cwd, home);
    if (home_path != NULL)
        display_path = home_path;
    if (isatty(STDIN_FILENO)) {
        printf("%s > ", display_path);
        fflush(stdout);
    }
    if (display_path != cwd)
        free(display_path);
}

static char *read_terminal_input(void)
{
    shell_data_t *sh = get_shell_instance();

    return read_line_raw(sh->term);
}

static char *read_file_input(void)
{
    char *input = NULL;
    size_t size = 0;
    ssize_t read;

    read = getline(&input, &size, stdin);
    if (read == -1) {
        free(input);
        return NULL;
    }
    if (input[read - 1] == '\n')
        input[read - 1] = '\0';
    return input;
}

char *read_input(void)
{
    if (isatty(STDIN_FILENO))
        return read_terminal_input();
    else
        return read_file_input();
}

int process_input(shell_data_t *sh, char *input)
{
    token_list_t *tokens;
    ast_t *ast;
    int exit_code = 0;

    if (input == NULL || input[0] == '\0')
        return sh->exit_code;
    add_to_history(sh->history, input);
    tokens = tokenize_input(input);
    if (tokens != NULL) {
        ast = parse_tokens(tokens);
        if (ast != NULL) {
            exit_code = execute_ast(ast);
            free_ast(ast);
        }
        free_token_list(tokens);
    }
    return exit_code;
}
