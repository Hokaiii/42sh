/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** variable builtins
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/shell.h"

status_t builtin_history(char **args)
{
    shell_data_t *sh = get_shell_instance();
    history_entry_t *entry = sh->history->head;
    int count = 0;

    while (entry != NULL) {
        printf("%5d  %s\n", count++, entry->command);
        entry = entry->next;
    }
    return SUCCESS;
}

status_t builtin_set(char **args)
{
    shell_data_t *sh = get_shell_instance();
    var_node_t *node;

    if (args[1] == NULL) {
        node = sh->vars->head;
        while (node != NULL) {
            printf("%s\t%s\n", node->key, node->value ? node->value : "");
            node = node->next;
        }
        return SUCCESS;
    }
    if (args[2] == NULL)
        add_var(sh->vars, args[1], "", false);
    else
        add_var(sh->vars, args[1], args[2], false);
    return SUCCESS;
}

status_t builtin_unset(char **args)
{
    shell_data_t *sh = get_shell_instance();

    if (args[1] == NULL) {
        fprintf(stderr, "unset: Too few arguments.\n");
        return ERROR;
    }
    for (int i = 1; args[i] != NULL; i++)
        remove_var(sh->vars, args[i]);
    return SUCCESS;
}
