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

static int save_stdin(int fd)
{
    shell_data_t *sh = get_shell_instance();
    int saved_fd;

    saved_fd = dup(STDIN_FILENO);
    if (saved_fd == -1) {
        perror("dup");
        close(fd);
        return -1;
    }
    sh->saved_stdin = saved_fd;
    return saved_fd;
}

static bool create_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return false;
    }
    return true;
}

static bool write_to_pipe(int pipefd[2], const char *content)
{
    if (write(pipefd[1], content, strlen(content)) == -1) {
        perror("write");
        close(pipefd[0]);
        close(pipefd[1]);
        return false;
    }
    return true;
}

static bool setup_heredoc_pipe(int pipefd[2], const char *content)
{
    if (!create_pipe(pipefd))
        return false;
    if (!write_to_pipe(pipefd, content))
        return false;
    close(pipefd[1]);
    return true;
}

static status_t execute_with_stdin_redirection(ast_node_t *node, int fd)
{
    shell_data_t *sh = get_shell_instance();
    status_t result;

    if (save_stdin(fd) == -1)
        return ERROR;
    handle_redirection(fd, STDIN_FILENO);
    result = execute_node(node->left);
    restore_redirection(STDIN_FILENO, sh->saved_stdin);
    sh->saved_stdin = -1;
    return result;
}

status_t execute_redirect_heredoc(ast_node_t *node)
{
    int pipefd[2];

    if (node == NULL || node->redirect_file == NULL || node->left == NULL)
        return ERROR;
    if (!setup_heredoc_pipe(pipefd, node->redirect_file))
        return ERROR;
    return execute_with_stdin_redirection(node, pipefd[0]);
}

static int open_input_file(const char *filename)
{
    int fd;

    if (!file_exists(filename)) {
        fprintf(stderr, "%s: No such file or directory\n", filename);
        return -1;
    }
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        perror(filename);
    return fd;
}

status_t execute_redirect_in(ast_node_t *node)
{
    int fd;

    if (node == NULL || node->redirect_file == NULL || node->left == NULL)
        return ERROR;
    fd = open_input_file(node->redirect_file);
    if (fd == -1)
        return ERROR;
    return execute_with_stdin_redirection(node, fd);
}

void handle_redirection(int old_fd, int new_fd)
{
    if (old_fd == -1 || new_fd == -1)
        return;
    if (old_fd != new_fd) {
        if (dup2(old_fd, new_fd) == -1) {
            perror("dup2");
            return;
        }
        if (close(old_fd) == -1) {
            perror("close");
        }
    }
}

void restore_redirection(int old_fd, int saved_fd)
{
    if (old_fd == -1 || saved_fd == -1)
        return;
    if (dup2(saved_fd, old_fd) == -1) {
        perror("dup2");
    }
    if (close(saved_fd) == -1) {
        perror("close");
    }
}
