/*
** EPITECH PROJECT, 2024
** get_path_env.c
** File description:
** get path from env
*/

#include "lib.h"
#include <string.h>
#include <stdlib.h>

char **get_path_env(char **env)
{
    char *goodline = NULL;
    char **path = NULL;

    for (int i = 0; env[i]; i++){
        if (strncmp("PATH=", env[i], 5) == 0){
            goodline = malloc(strlen(env[i]) - 4);
            strncpy(goodline, env[i] + 5, strlen(env[i]) - 5);
            path = the_str_to_word_array(goodline,
                (char *[]) { ":", NULL }, NULL);
            break;
        }
    }
    if (goodline)
        free(goodline);
    return (path);
}
