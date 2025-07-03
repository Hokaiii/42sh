/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Header file
*/

#ifndef BUILTINS_H
    #define BUILTINS_H

    #include "types.h"

typedef struct builtin_s {
    char *name;
    status_t (*func)(char **args);
} builtin_t;

status_t builtin_cd(char **args);
status_t builtin_exit(char **args);
status_t builtin_env(char **args);
status_t builtin_setenv(char **args);
status_t builtin_unsetenv(char **args);
status_t builtin_echo(char **args);
status_t builtin_which(char **args);
status_t builtin_where(char **args);
status_t builtin_history(char **args);
status_t builtin_set(char **args);
status_t builtin_unset(char **args);
status_t builtin_repeat(char **args);
status_t builtin_alias(char **args);

extern const builtin_t BUILTINS[];
int is_builtin(const char *cmd);
status_t execute_builtin(char **args);

#endif
