/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Core builtins
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/shell.h"

const builtin_t BUILTINS[] = {
    {"cd", &builtin_cd},
    {"exit", &builtin_exit},
    {"env", &builtin_env},
    {"setenv", &builtin_setenv},
    {"unsetenv", &builtin_unsetenv},
    {"echo", &builtin_echo},
    {"which", &builtin_which},
    {"where", &builtin_where},
    {"history", &builtin_history},
    {"set", &builtin_set},
    {"unset", &builtin_unset},
    {"repeat", &builtin_repeat},
    {"alias", &builtin_alias},
    {NULL, NULL}
};

int is_builtin(const char *cmd)
{
    for (int i = 0; BUILTINS[i].name != NULL; i++) {
        if (strcmp(BUILTINS[i].name, cmd) == 0)
            return 1;
    }
    return 0;
}

status_t execute_builtin(char **args)
{
    for (int i = 0; BUILTINS[i].name != NULL; i++) {
        if (strcmp(BUILTINS[i].name, args[0]) == 0)
            return BUILTINS[i].func(args);
    }
    return ERROR;
}

status_t builtin_exit(char **args)
{
    shell_data_t *sh = get_shell_instance();
    int exit_code = 0;

    if (args[1] != NULL) {
        exit_code = atoi(args[1]);
        if (exit_code < 0)
            exit_code = 0;
    }
    sh->exit_code = exit_code;
    sh->should_exit = true;
    return SUCCESS;
}
