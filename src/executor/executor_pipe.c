/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** pipe execution functions
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "../../include/shell.h"

static pid_t create_left_pipe_process(int *pipefd, ast_node_t *left_node)
{
    pid_t pid = fork();
    status_t exit_status;

    if (pid == -1)
        return -1;
    if (pid == 0) {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            close(pipefd[1]);
            exit(ERROR);
        }
        close(pipefd[1]);
        exit_status = execute_node(left_node);
        exit(exit_status);
    }
    return pid;
}

static pid_t create_right_pipe_process(int *pipefd, ast_node_t *right_node)
{
    pid_t pid = fork();
    status_t exit_status;

    if (pid == -1)
        return -1;
    if (pid == 0) {
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            close(pipefd[0]);
            exit(ERROR);
        }
        close(pipefd[0]);
        exit_status = execute_node(right_node);
        exit(exit_status);
    }
    return pid;
}

static status_t get_status_from_wait(int status)
{
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status))
        return 128 + WTERMSIG(status);
    return ERROR;
}

static status_t get_exit_status(int status1, int status2)
{
    status_t result;

    result = get_status_from_wait(status2);
    if (result != ERROR)
        return result;
    return get_status_from_wait(status1);
}

static bool setup_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return false;
    }
    return true;
}

static bool create_pipe_processes(int pipefd[2], ast_node_t *node,
    pid_t *pid1, pid_t *pid2)
{
    *pid1 = create_left_pipe_process(pipefd, node->left);
    if (*pid1 == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return false;
    }
    *pid2 = create_right_pipe_process(pipefd, node->right);
    if (*pid2 == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        kill(*pid1, SIGTERM);
        waitpid(*pid1, NULL, 0);
        return false;
    }
    return true;
}

status_t execute_pipe(ast_node_t *node)
{
    int pipefd[2];
    pid_t pid1;
    pid_t pid2;
    int status1;
    int status2;

    if (node == NULL || node->left == NULL || node->right == NULL)
        return ERROR;
    if (!setup_pipe(pipefd))
        return ERROR;
    if (!create_pipe_processes(pipefd, node, &pid1, &pid2))
        return ERROR;
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);
    return get_exit_status(status1, status2);
}
