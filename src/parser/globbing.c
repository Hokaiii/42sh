/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbing
*/

#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <stdbool.h>
#include "../../include/shell.h"

static bool has_glob_pattern(const char *str)
{
    if (str == NULL)
        return false;
    return (strchr(str, '*') != NULL || strchr(str, '?') != NULL ||
            strchr(str, '[') != NULL);
}

static int count_args(char **args)
{
    int count = 0;

    if (args == NULL)
        return 0;
    while (args[count] != NULL)
        count++;
    return count;
}

static void free_args(char **args)
{
    int i = 0;

    for (i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}

static int copy_args_with_glob(char **new_args, char **args,
    int arg_index, glob_t *glob_result)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < arg_index; i++)
        new_args[i] = strdup(args[i]);
    for (j = 0; j < (int)glob_result->gl_pathc; j++) {
        new_args[i] = strdup(glob_result->gl_pathv[j]);
        i++;
    }
    for (j = arg_index + 1; args[j] != NULL; j++) {
        new_args[i] = strdup(args[j]);
        i++;
    }
    return i;
}

static char **add_glob_matches(char **args, int arg_index, glob_t *glob_result)
{
    int new_count = count_args(args) - 1 + (int)glob_result->gl_pathc;
    char **new_args = malloc(sizeof(char *) * (new_count + 1));
    int i = 0;

    if (new_args == NULL)
        return args;
    i = copy_args_with_glob(new_args, args, arg_index, glob_result);
    new_args[i] = NULL;
    free_args(args);
    return new_args;
}

static void process_glob_pattern(char ***args, int *i, glob_t *glob_result)
{
    if (glob_result->gl_pathc > 0) {
        *args = add_glob_matches(*args, *i, glob_result);
        *i += (int)glob_result->gl_pathc - 1;
    }
    globfree(glob_result);
}

static void handle_single_arg(char ***args, int *i)
{
    glob_t glob_result;
    int glob_flags = GLOB_NOCHECK;

    if (has_glob_pattern((*args)[*i])) {
        if (glob((*args)[*i], glob_flags, NULL, &glob_result) == 0) {
            process_glob_pattern(args, i, &glob_result);
        }
    }
}

void handle_globbing(char ***args)
{
    int i = 0;

    if (args == NULL || *args == NULL)
        return;
    while ((*args)[i] != NULL) {
        handle_single_arg(args, &i);
        i++;
    }
}
