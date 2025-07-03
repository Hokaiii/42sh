/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** builtin_alias
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../../../include/shell.h"
#include "../../../include/alias.h"

alias_list_t *init_alias_list(void)
{
    alias_list_t *list = malloc(sizeof(alias_list_t));

    if (!list)
        return NULL;
    list->head = NULL;
    list->size = 0;
    return list;
}

int check_quote_balance(const char *value)
{
    int single_quote = 0;
    int double_quote = 0;
    int i = 0;

    if (!value)
        return 0;
    while (value[i]) {
        if (value[i] == '\'')
            single_quote++;
        if (value[i] != '\'' && value[i] == '"')
            double_quote++;
        i++;
    }
    return (single_quote % 2 == 0) && (double_quote % 2 == 0);
}

int is_quotes(char *value)
{
    int len = strlen(value);

    if (len < 2)
        return 0;
    return ((value[0] == '"' && value[len - 1] == '"') ||
            (value[0] == '\'' && value[len - 1] == '\''));
}

void remove_quotes(char **value)
{
    int len = strlen(*value);

    (*value)[len - 1] = '\0';
    (*value)++;
}

int parse_alias(char *arg, char **name, char **value)
{
    char *equal_char = NULL;

    equal_char = strchr(arg, '=');
    if (!equal_char)
        return 1;
    *equal_char = '\0';
    *name = arg;
    *value = equal_char + 1;
    if (!check_quote_balance(*value))
        return 1;
    if (is_quotes(*value))
        remove_quotes(value);
    return 0;
}
