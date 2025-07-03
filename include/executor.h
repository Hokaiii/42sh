/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Header file
*/

#ifndef EXECUTOR_H
    #define EXECUTOR_H

    #include "types.h"
    #include "parser.h"

status_t execute_ast(ast_t *ast);
status_t execute_node(ast_node_t *node);
status_t execute_command(ast_node_t *node);
status_t execute_command_args(char **args);
status_t execute_pipe(ast_node_t *node);
status_t execute_redirect_in(ast_node_t *node);
status_t execute_redirect_out(ast_node_t *node);
status_t execute_redirect_append(ast_node_t *node);
status_t execute_redirect_heredoc(ast_node_t *node);
status_t execute_and(ast_node_t *node);
status_t execute_or(ast_node_t *node);
status_t execute_semicolon(ast_node_t *node);
status_t execute_background(ast_node_t *node);

void handle_redirection(int old_fd, int new_fd);
void restore_redirection(int old_fd, int saved_fd);

#endif
