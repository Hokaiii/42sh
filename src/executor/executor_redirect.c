/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** redirection functions
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../include/shell.h"

static int open_output_file(const char *filename, int flags)
{
    int fd;

    fd = open(filename, flags, 0644);
    if (fd == -1)
        perror(filename);
    return fd;
}

static int save_stdout(int fd)
{
    shell_data_t *sh = get_shell_instance();
    int saved_fd;

    saved_fd = dup(STDOUT_FILENO);
    if (saved_fd == -1) {
        perror("dup");
        close(fd);
        return -1;
    }
    sh->saved_stdout = saved_fd;
    return saved_fd;
}

static status_t execute_with_stdout_redirection(ast_node_t *node, int fd)
{
    shell_data_t *sh = get_shell_instance();
    status_t result;

    if (save_stdout(fd) == -1)
        return ERROR;
    handle_redirection(fd, STDOUT_FILENO);
    result = execute_node(node->left);
    restore_redirection(STDOUT_FILENO, sh->saved_stdout);
    sh->saved_stdout = -1;
    return result;
}

status_t execute_redirect_out(ast_node_t *node)
{
    int fd;

    if (node == NULL || node->redirect_file == NULL || node->left == NULL)
        return ERROR;
    fd = open_output_file(node->redirect_file, O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1)
        return ERROR;
    return execute_with_stdout_redirection(node, fd);
}

status_t execute_redirect_append(ast_node_t *node)
{
    int fd;

    if (node == NULL || node->redirect_file == NULL || node->left == NULL)
        return ERROR;
    fd = open_output_file(node->redirect_file, O_WRONLY | O_CREAT | O_APPEND);
    if (fd == -1)
        return ERROR;
    return execute_with_stdout_redirection(node, fd);
}
