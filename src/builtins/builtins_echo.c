/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Echo builtin
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/shell.h"

status_t builtin_echo(char **args)
{
    int i = 1;
    int newline = 1;

    if (args[1] != NULL && strcmp(args[1], "-n") == 0) {
        newline = 0;
        i++;
    }
    while (args[i] != NULL) {
        printf("%s", args[i]);
        if (args[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
    return SUCCESS;
}
