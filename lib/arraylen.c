/*
** EPITECH PROJECT, 2024
** arraylen
** File description:
** return the len of a char
*/

int arraylen(char **array)
{
    int length = 0;

    for (; array[length]; length++);
    return length;
}
