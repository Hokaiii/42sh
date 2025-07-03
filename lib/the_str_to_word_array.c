/*
** EPITECH PROJECT, 2024
** the_str_to_word_array
** File description:
** the ultimate form of str_to_word_array
*/

#include "lib.h"
#include "lib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int count_charx(char *str, char **divide, char **kdivide)
{
    int count = 0;

    for (int i = 0; i <= (int)strlen(str); i++){
        for (int j = 0; divide && divide[j]; j++){
            count = (str[i] && strncmp(&str[i], divide[j],
            strlen(divide[j])) == 0 && strlen(&str[i]) >
            strlen(divide[j]) + 1) ? count + 1 : count;
            i += (str[i] && strncmp(&str[i], divide[j]
            , strlen(divide[j])) == 0) ? strlen(divide[j]) : 0;
        }
        for (int j = 0; kdivide && kdivide[j]; j++){
            count = (str[i] && strncmp(&str[i], kdivide[j],
            strlen(kdivide[j])) == 0 && strlen(&str[i]) >
            strlen(kdivide[j]) + 1) ? count + 2 : count;
            i += (str[i] && strncmp(&str[i], kdivide[j],
            strlen(kdivide[j])) == 0) ? strlen(kdivide[j]) : 0;
        }
    }
    return count + 1;
}

/*
for the next functions, I needed to use an int * to follow the coding style
val[0] is the lenght of word array
val[1] is the beginning of a word
val[2] is the current index in word array
val[3] is the global loop counter to travel in the string
val[4] is the partial loop counter to travel in the divider
*/
static void process_divide(char **word_array
    , char *str, char **divide, int *val)
{
    if (strncmp(&str[val[3]], divide[val[4]], strlen(divide[val[4]]))
        == 0){
        if (val[3] > val[1]){
            word_array[val[2]] = strndup(&str[val[1]], val[3] - val[1]);
            val[2]++;
        }
    val[1] = val[3] + strlen(divide[val[4]]);
    val[3] = val[1] - 1;
    }
}

static void process_kdivide(char **word_array
    , char *str, char **kdivide, int *val)
{
    if (strncmp(&str[val[3]], kdivide[val[4]]
        , strlen(kdivide[val[4]])) == 0 && val[3] >= val[1]){
        if (val[3] == val[1])
            val[2]--;
        if (val[3] != val[1])
            word_array[val[2]] = strndup(&str[val[1]], val[3] - val[1]);
        word_array[val[2] + 1] = strdup(kdivide[val[4]]);
        val[2] += 2;
        val[1] = val[3] + strlen(kdivide[val[4]]);
        val[3] = val[1] - 1;
    }
}

char **the_str_to_word_array(char *str, char **divide, char **kdivide)
{
    int *val = malloc(sizeof(int) * 5);
    char **word_array = NULL;

    val[0] = count_charx(str, divide, kdivide);
    val[1] = 0;
    val[2] = 0;
    word_array = malloc(sizeof(char *) * (val[0] + 1));
    for (val[3] = 0; str[val[3]]; val[3]++){
        for (val[4] = 0; divide[val[4]]; val[4]++)
            process_divide(word_array, str, divide, val);
        for (val[4] = 0; kdivide[val[4]]; val[4]++)
            process_kdivide(word_array, str, kdivide, val);
    }
    if (val[0] > val[2] && str[val[1]] != '\0'){
        word_array[val[2]] = strndup(&str[val[1]], strlen(str));
        val[2]++;
    }
    word_array[val[2]] = NULL;
    free(val);
    return word_array;
}
