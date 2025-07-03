/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Header file
*/

#ifndef CONSTANTS_H
    #define CONSTANTS_H

    #define SUCCESS 0
    #define ERROR 1
    #define CHILD_PROCESS -1

    #define READ_END 0
    #define WRITE_END 1

    #define MAX_PATH_LENGTH 4096
    #define MAX_INPUT_LENGTH 4096
    #define MAX_ARGS 256

    #define CTRL_A 1
    #define CTRL_D 4
    #define CTRL_E 5
    #define CTRL_K 11
    #define CTRL_L 12
    #define CTRL_U 21
    #define CTRL_W 23
    #define BACKSPACE 127
    #define ESCAPE 27
    #define TAB 9
    #define ENTER 10

    #define HISTORY_FILE ".42sh_history"
    #define CONFIG_FILE ".42shrc"

#endif
