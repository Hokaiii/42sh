/*
** EPITECH PROJECT, 2025
** concat_str
** File description:
** concat string
*/

#include "lib.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

char *str_concat(char *s1, char *s2)
{
    char *output = my_calloc(strlen(s1) + strlen(s2) + 1);

    strcat(output, s1);
    strcat(output, s2);
    free(s1);
    return output;
}

char *superstrcat(char *chain, ...)
{
    va_list args;
    char *output = my_calloc(strlen(chain) + 1);

    va_start(args, chain);
    while (chain) {
        output = str_concat(output, chain);
        chain = va_arg(args, char *);
    }
    va_end(args);
    return output;
}
