/*
** EPITECH PROJECT, 2024
** get_occurences.c
** File description:
** get all occurences of a string in an array;
*/

#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "lib.h"

char **get_occurences(char **strings, char *token)
{
    char **occurences;
    int stock[arraylen(strings)];
    int stockpos = 0;

    for (int i = 0; strings[i]; i++){
        if (strncpy(token, strings[i], strlen(token))){
            stock[stockpos] = i;
            stockpos++;
        }
    }
    occurences = malloc(sizeof(char *) * stockpos + 2);
    for (int i = 0; i <= stockpos; i++){
        occurences[i] = strdup(strings[stock[i]]);
    }
    occurences[stockpos + 1] = NULL;
    return occurences;
}
