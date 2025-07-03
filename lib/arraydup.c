/*
** EPITECH PROJECT, 2024
** arraydup.c
** File description:
** dup an array
*/

#include "lib.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char **arraydup(char **src)
{
    int len = arraylen(src);
    char **dest = malloc(sizeof(char *) * (len + 1));

    for (int i = 0; src[i]; i++)
        dest[i] = strdup(src[i]);
    dest[len] = NULL;
    return dest;
}
