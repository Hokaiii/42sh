/*
** EPITECH PROJECT, 2025
** better_malloc.c
** File description:
** better malloc
*/
#include <stddef.h>
#include <stdlib.h>

char *my_calloc(int size)
{
    char *loc = malloc(size);

    if (loc == NULL)
        return NULL;
    for (int i = 0; i != size; i++)
        loc[i] = 0;
    return loc;
}

char *initchar(int size, char *str)
{
    for (int i = 0; i != size; i++)
        str[i] = 0;
    return str;
}

void bfree(void *thing)
{
    if (thing != NULL)
        free(thing);
}
