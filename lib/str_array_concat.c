/*
** EPITECH PROJECT, 2025
** str_array_cat
** File description:
** concatenate 2 array into a new one
*/

#include "lib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char **strarraycat(char **array1, char **array2)
{
    char **new_array = malloc(sizeof(char *)
        * (arraylen(array1) + arraylen(array2) + 1));
    int i = 0;

    for (; array1[i]; i++)
        new_array[i] = strdup(array1[i]);
    for (int j = 0; array2[j]; j++){
        new_array[i] = strdup(array2[j]);
        i++;
    }
    new_array[i] = NULL;
    return new_array;
}
