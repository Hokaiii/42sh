/*
** EPITECH PROJECT, 2024
** get_dir_files.c
** File description:
** return an array containing all files name in a dir
*/

#include <dirent.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int count_files(const char *folder)
{
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir(folder);
    if (dir == NULL)
        return -1;
    entry = readdir(dir);
    while (entry != NULL) {
        count++;
        entry = readdir(dir);
    }
    closedir(dir);
    return count;
}

char **get_files_dir(const char *folder)
{
    DIR *dir;
    int file_nb = count_files(folder);
    char **file_list = calloc(file_nb - 1, sizeof(char *));
    int i = 0;

    dir = opendir(folder);
    if (!dir){
        return NULL;
    }
    for (struct dirent *entry = readdir(dir); i < file_nb - 2;
        entry = readdir(dir)){
        if (strcmp(entry->d_name, ".") != 0
            && strcmp(entry->d_name, "..") != 0){
            asprintf(&file_list[i], "%s/%s", folder, entry->d_name);
            i++;
        }
    }
    closedir(dir);
    return file_list;
}
