/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** repeat builtin
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/shell.h"

status_t builtin_repeat(char **args)
{
    int count;
    char **cmd_args;
    status_t status = SUCCESS;

    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "repeat: Too few arguments.\n");
        return ERROR;
    }
    count = atoi(args[1]);
    if (count <= 0)
        return SUCCESS;
    cmd_args = &args[2];
    for (int i = 0; i < count; i++) {
        if (is_builtin(cmd_args[0]))
            status = execute_builtin(cmd_args);
        else
            status = execute_command_args(cmd_args);
    }
    return status;
}
