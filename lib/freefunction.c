/*
** EPITECH PROJECT, 2025
** freefunction.c
** File description:
** 2Befree
** functions to free array;
*/

#include "lib.h"
#include <stdlib.h>

void free_char_2x(char **char2x)
{
    for (int i = 0; char2x[i]; i++){
        free(char2x[i]);
    }
    free(char2x);
}

void free_char_3x(char ***char3x)
{
    for (int i = 0; char3x[i]; i++){
        for (int j = 0; char3x[i][j]; j++)
            free(char3x[i][j]);
        free(char3x[i]);
    }
    free(char3x);
}
