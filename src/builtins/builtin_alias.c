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
#include "../../include/shell.h"
#include "../../include/alias.h"

static char **check_and_replace_alias(char **args, alias_list_t *aliases)
{
    const char *alias_value;

    if (!args || !args[0] || !aliases)
        return args;
    alias_value = get_alias(aliases, args[0]);
    if (!alias_value)
        return args;
    free(args[0]);
    args[0] = strdup(alias_value);
    if (!args[0])
        return NULL;
    return args;
}

status_t builtin_alias(char **args)
{
    shell_data_t *sh = get_shell_instance();
    alias_list_t *alias_list = sh->aliases;
    char *name = NULL;
    char *value = NULL;

    if (!args[1]) {
        print_alias_list(alias_list);
        return 0;
    }
    if (parse_alias(args[1], &name, &value) != 0)
        return 1;
    if (add_alias(alias_list, name, value) != 0)
        return 1;
    args = check_and_replace_alias(args, sh->aliases);
    if (!args)
        return 1;
    return SUCCESS;
}
