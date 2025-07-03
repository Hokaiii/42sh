/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Core exec
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../../include/shell.h"

status_t execute_ast(ast_t *ast)
{
    if (ast == NULL || ast->root == NULL)
        return SUCCESS;
    if (ast->error != ERROR_NONE) {
        fprintf(stderr, "Syntax error\n");
        return ERROR;
    }
    return execute_node(ast->root);
}

static status_t handle_command_execution(char *path, char **args, char **env)
{
    execve(path, args, env);
    perror(args[0]);
    free(path);
    exit(ERROR);
    return ERROR;
}

static status_t handle_child_process(char *path, char **args)
{
    shell_data_t *sh = get_shell_instance();
    char **env = env_to_array(sh->env);

    return handle_command_execution(path, args, env);
}

static status_t wait_for_child(pid_t pid)
{
    shell_data_t *sh = get_shell_instance();
    int status;

    sh->current_pid = pid;
    waitpid(pid, &status, 0);
    sh->current_pid = 0;
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGSEGV)
            fprintf(stderr, "Segmentation fault\n");
        return 128 + WTERMSIG(status);
    }
    return ERROR;
}

static status_t execute_external_command(char **args, char *path)
{
    pid_t pid;
    status_t result;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        free(path);
        return ERROR;
    }
    if (pid == 0)
        return handle_child_process(path, args);
    result = wait_for_child(pid);
    free(path);
    return result;
}

status_t execute_command_args(char **args)
{
    char *path;

    if (args == NULL || args[0] == NULL)
        return SUCCESS;
    if (is_builtin(args[0]))
        return execute_builtin(args);
    path = find_executable(args[0]);
    if (path == NULL) {
        fprintf(stderr, "%s: Command not found.\n", args[0]);
        return ERROR;
    }
    return execute_external_command(args, path);
}

status_t execute_command(ast_node_t *node)
{
    if (node == NULL)
        return SUCCESS;
    return execute_command_args(node->args);
}

status_t execute_node(ast_node_t *node)
{
    if (node == NULL)
        return SUCCESS;
    for (int i = 0; node_exec_map[i].type != NODE_UNKNOWN; i++) {
        if (node_exec_map[i].type == node->type) {
            return node_exec_map[i].execute(node);
        }
    }
    return ERROR;
}
