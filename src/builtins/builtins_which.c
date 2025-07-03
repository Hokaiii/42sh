/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** builtins implementation
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../../include/shell.h"

static status_t process_which_command(const char *cmd)
{
    char *path;

    if (is_builtin(cmd)) {
        printf("%s: shell built-in command.\n", cmd);
        return SUCCESS;
    }
    path = find_executable((char *)cmd);
    if (path != NULL) {
        printf("%s\n", path);
        free(path);
        return SUCCESS;
    }
    fprintf(stderr, "%s: Command not found.\n", cmd);
    return ERROR;
}

status_t builtin_which(char **args)
{
    status_t status = SUCCESS;

    if (args[1] == NULL) {
        fprintf(stderr, "which: Too few arguments.\n");
        return ERROR;
    }
    for (int i = 1; args[i] != NULL && status == SUCCESS; i++)
        status = process_which_command(args[i]);
    return status;
}

static void print_builtin_status(const char *cmd)
{
    if (is_builtin(cmd))
        printf("%s is a shell built-in\n", cmd);
}

static void find_in_path(const char *cmd, const char *path_env)
{
    char *path_copy = strdup(path_env);
    char *path = strtok(path_copy, ":");
    char *full_path;

    while (path != NULL) {
        full_path = malloc(strlen(path) + strlen(cmd) + 2);
        if (full_path == NULL) {
            free(path_copy);
            return;
        }
        sprintf(full_path, "%s/%s", path, cmd);
        if (access(full_path, X_OK) == 0)
            printf("%s\n", full_path);
        free(full_path);
        path = strtok(NULL, ":");
    }
    free(path_copy);
}

status_t builtin_where(char **args)
{
    char *path_env;
    shell_data_t *sh = get_shell_instance();

    if (args[1] == NULL) {
        fprintf(stderr, "where: Too few arguments.\n");
        return ERROR;
    }
    path_env = get_env_var(sh->env, "PATH");
    if (path_env == NULL)
        return ERROR;
    for (int i = 1; args[i] != NULL; i++) {
        print_builtin_status(args[i]);
        find_in_path(args[i], path_env);
    }
    return SUCCESS;
}
