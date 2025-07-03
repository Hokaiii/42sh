/*
** EPITECH PROJECT, 2025
** is_a_binary
** File description:
** search if a file is a binary
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int is_a_bin(char **path, char *command)
{
    char *filename;

    for (int i = 0; path[i]; i++){
        asprintf(&filename, "%s/%s", path[i], command);
        if (access(filename, F_OK) == 0){
            free(filename);
            return 1;
        }
        free(filename);
    }
    asprintf(&filename, "./%s", command);
    if (access(filename, F_OK) == 0){
        free(filename);
        return 1;
    }
    free(filename);
    return 0;
}
