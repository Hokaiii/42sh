/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Shell utility functions
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../../include/shell.h"

bool is_directory(const char *path)
{
    struct stat st;

    if (stat(path, &st) == 0)
        return S_ISDIR(st.st_mode);
    return false;
}

bool file_exists(const char *path)
{
    return access(path, F_OK) == 0;
}

static bool is_path_command(const char *cmd)
{
    if (cmd == NULL || cmd[0] == '\0')
        return false;
    return (cmd[0] == '/' || cmd[0] == '.');
}

static char *find_in_path(const char *path, const char *cmd)
{
    char *full_path;

    full_path = malloc(strlen(path) + strlen(cmd) + 2);
    if (full_path == NULL)
        return NULL;
    sprintf(full_path, "%s/%s", path, cmd);
    if (access(full_path, X_OK) == 0)
        return full_path;
    free(full_path);
    return NULL;
}

static char *search_in_paths(char *path_env, const char *cmd)
{
    char *path_copy = strdup(path_env);
    char *path = strtok(path_copy, ":");
    char *full_path;

    while (path != NULL) {
        full_path = find_in_path(path, cmd);
        if (full_path != NULL) {
            free(path_copy);
            return full_path;
        }
        path = strtok(NULL, ":");
    }
    free(path_copy);
    return NULL;
}

char *find_executable(char *cmd)
{
    shell_data_t *sh = get_shell_instance();
    char *path_env = get_env_var(sh->env, "PATH");

    if (cmd == NULL || cmd[0] == '\0')
        return NULL;
    if (is_path_command(cmd))
        return access(cmd, X_OK) == 0 ? strdup(cmd) : NULL;
    if (path_env == NULL)
        return NULL;
    return search_in_paths(path_env, cmd);
}
