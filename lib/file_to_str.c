/*
** EPITECH PROJECT, 2025
** file_to_str
** File description:
** Convert a file to a string.
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int get_file_size(char const *file)
{
    char buffer[32001];
    int size = 0;
    int rd_size = 0;
    int fd = 0;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        return -1;
    rd_size = read(fd, buffer, 32000);
    size += rd_size;
    while (rd_size > 0){
        rd_size = read(fd, buffer, 32000);
        size += rd_size;
    }
    close(fd);
    return size;
}

char *file_to_str(char const *file)
{
    int size = get_file_size(file);
    char *save = (size >= 0) ? malloc(size + 1) : NULL;
    int fd = 0;

    fd = open(file, O_RDONLY);
    if (!save || fd == -1)
        return NULL;
    read(fd, save, size);
    save[size] = '\0';
    close(fd);
    return save;
}

char *file_to_str_wsize(char const *file, int size)
{
    int file_size = get_file_size(file);
    char *save = (file_size >= 0) ? malloc(size) : NULL;
    int fd = 0;

    if (save)
        fd = open(file, O_RDONLY);
    if (!fd)
        return NULL;
    read(fd, save, size);
    if (file_size < size)
        save[file_size] = '\0';
    else
        save[size] = '\0';
    close(fd);
    return save;
}
