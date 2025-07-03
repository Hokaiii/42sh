/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Header file
*/

#ifndef SHELL_H
    #define SHELL_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdbool.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <signal.h>
    #include <errno.h>
    #include <dirent.h>
    #include <termios.h>
    #include <limits.h>
    #include <ctype.h>
    #include <time.h>

    #include "constants.h"
    #include "types.h"
    #include "env.h"
    #include "parser.h"
    #include "builtins.h"
    #include "executor.h"
    #include "terminal.h"
    #include "history.h"
    #include "alias.h"
    #include "../lib/lib.h"

typedef struct shell_data_s {
    env_list_t *env;
    var_list_t *vars;
    alias_list_t *aliases;
    char *input_buffer;
    char *current_dir;
    char *previous_dir;
    char *home_dir;
    int exit_code;
    bool should_exit;
    pid_t current_pid;
    int saved_stdin;
    int saved_stdout;
    terminal_t *term;
    history_t *history;
} shell_data_t;

typedef struct {
    node_type_t type;
    status_t (*execute)(ast_node_t *node);
} node_exec_map_t;

status_t execute_command(ast_node_t *node);
status_t execute_command_args(char **args);
status_t execute_pipe(ast_node_t *node);
status_t execute_redirect_in(ast_node_t *node);
status_t execute_redirect_out(ast_node_t *node);
status_t execute_redirect_append(ast_node_t *node);
status_t execute_and(ast_node_t *node);
status_t execute_or(ast_node_t *node);
status_t execute_semicolon(ast_node_t *node);
status_t execute_background(ast_node_t *node);

static const node_exec_map_t node_exec_map[] = {
    {NODE_COMMAND, execute_command},
    {NODE_PIPE, execute_pipe},
    {NODE_REDIR_IN, execute_redirect_in},
    {NODE_REDIR_OUT, execute_redirect_out},
    {NODE_REDIR_APPEND, execute_redirect_append},
    {NODE_AND, execute_and},
    {NODE_OR, execute_or},
    {NODE_SEMICOLON, execute_semicolon},
    {NODE_BACKGROUND, execute_background},
    {NODE_UNKNOWN, NULL}
};

shell_data_t *get_shell_instance(void);
int initialize_shell(char **environ);
int run_shell_loop(void);
int cleanup_shell(void);
void display_prompt(void);
char *read_input(void);
int process_input(shell_data_t *sh, char *input);
void handle_signals(void);
char *find_executable(char *cmd);
bool is_directory(const char *path);
bool file_exists(const char *path);
void handle_tab_completion(terminal_t *term);
void handle_escape_sequence(terminal_t *term, shell_data_t *sh);
void free_alias_list(alias_list_t *list);
void ncurses_process(void);

#endif
