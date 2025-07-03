/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** CD builtin
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "../../include/shell.h"

static char *get_target_directory(char **args)
{
    shell_data_t *sh = get_shell_instance();

    if (args[1] == NULL || strcmp(args[1], "~") == 0)
        return sh->home_dir;
    else if (strcmp(args[1], "-") == 0)
        return sh->previous_dir;
    else
        return args[1];
}

static int update_directory_vars(char *old_dir)
{
    shell_data_t *sh = get_shell_instance();

    free(sh->previous_dir);
    sh->previous_dir = old_dir;
    free(sh->current_dir);
    sh->current_dir = getcwd(NULL, 0);
    add_env_var(sh->env, "PWD", sh->current_dir);
    add_env_var(sh->env, "OLDPWD", sh->previous_dir);
    return SUCCESS;
}

static int check_target_error(char *target_dir, char **args)
{
    if (target_dir != NULL)
        return SUCCESS;
    if (args[1] == NULL || strcmp(args[1], "~") == 0) {
        fprintf(stderr, "cd: HOME not set\n");
        return ERROR;
    }
    if (strcmp(args[1], "-") == 0) {
        fprintf(stderr, "cd: OLDPWD not set\n");
        return ERROR;
    }
    fprintf(stderr, "cd: invalid target\n");
    return ERROR;
}

static int check_file_error(char *target_dir)
{
    struct stat st;

    if (stat(target_dir, &st) != SUCCESS) {
        fprintf(stderr, "cd: %s: No such file or directory\n", target_dir);
        return ERROR;
    }
    if (!S_ISDIR(st.st_mode)) {
        fprintf(stderr, "cd: %s: Not a directory\n", target_dir);
        return ERROR;
    }
    return SUCCESS;
}

static int check_dir_error(char *target_dir, char *old_dir)
{
    if (!old_dir)
        return ERROR;
    if (chdir(target_dir) == -1) {
        perror(target_dir);
        free(old_dir);
        return ERROR;
    }
    return SUCCESS;
}

status_t builtin_cd(char **args)
{
    shell_data_t *sh = get_shell_instance();
    char *target_dir = NULL;
    char *old_dir = NULL;

    if (args[2] != NULL) {
        fprintf(stderr, "cd: Too many arguments.\n");
        return ERROR;
    }
    target_dir = get_target_directory(args);
    old_dir = strdup(sh->current_dir);
    if (check_target_error(target_dir, args) != SUCCESS)
        return ERROR;
    if (check_file_error(target_dir) != SUCCESS)
        return ERROR;
    if (check_dir_error(target_dir, old_dir) != SUCCESS)
        return ERROR;
    return update_directory_vars(old_dir);
}
