/*
** EPITECH PROJECT, 2024
** insert char
** File description:
** delete a char in a str
*/
#include "lib.h"
#include <string.h>

void delete_char(char *str, int pos)
{
    int len = strlen(str);

    if (pos < 0 || pos >= len)
        return;
    for (int i = pos; i < len; i++) {
        str[i] = str[i + 1];
    }
}
