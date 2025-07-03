/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** env builtins
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "../../include/shell.h"

status_t builtin_env(char **args)
{
    shell_data_t *sh = get_shell_instance();
    env_node_t *node = sh->env->head;

    (void)args;
    while (node != NULL) {
        printf("%s=%s\n", node->key, node->value ? node->value : "");
        node = node->next;
    }
    return SUCCESS;
}

static bool is_valid_var_name(const char *name)
{
    if (name == NULL || !isalpha(name[0]))
        return false;
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalnum(name[i]) && name[i] != '_')
            return false;
    }
    return true;
}

static status_t print_var_name_error(const char *name)
{
    if (name != NULL && !isalpha(name[0]))
        fprintf(stderr, "setenv: Variable name must begin with a letter.\n");
    else
        fprintf(stderr, "setenv: Variable name must contain "
            "alphanumeric characters.\n");
    return ERROR;
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

status_t builtin_setenv(char **args)
{
    shell_data_t *sh = get_shell_instance();
    int arg_count = count_args(args);

    if (arg_count == 1) {
        return builtin_env(args);
    } else if (arg_count > 3) {
        fprintf(stderr, "setenv: Too many arguments.\n");
        return ERROR;
    }
    if (!is_valid_var_name(args[1]))
        return print_var_name_error(args[1]);
    if (arg_count == 2)
        add_env_var(sh->env, args[1], "");
    else
        add_env_var(sh->env, args[1], args[2]);
    return SUCCESS;
}

status_t builtin_unsetenv(char **args)
{
    shell_data_t *sh = get_shell_instance();

    if (args[1] == NULL) {
        fprintf(stderr, "unsetenv: Too few arguments.\n");
        return ERROR;
    }
    for (int i = 1; args[i] != NULL; i++)
        remove_env_var(sh->env, args[i]);
    return SUCCESS;
}
