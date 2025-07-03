/*
** EPITECH PROJECT, 2024
** insert char
** File description:
** insert a char in a str
*/

#include "lib.h"
#include <string.h>
#include <stdlib.h>

void insert_char(char *str, char c, int pos)
{
    int len = strlen(str);

    for (int i = len; i >= pos; i--)
        str[i + 1] = str[i];
    str[pos] = c;
}
