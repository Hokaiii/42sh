/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Shell initialization functions
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../include/shell.h"

static int init_shell_env(shell_data_t *sh, char **environ)
{
    char *key;
    char *value;

    sh->env = init_env_list();
    if (sh->env == NULL)
        return ERROR;
    for (int i = 0; environ[i] != NULL; i++) {
        key = strdup(environ[i]);
        value = strchr(key, '=');
        if (value != NULL) {
            *value = '\0';
            value++;
            add_env_var(sh->env, key, value);
        }
        free(key);
    }
    return SUCCESS;
}

static int init_shell_dirs(shell_data_t *sh)
{
    char *home = get_env_var(sh->env, "HOME");

    sh->home_dir = home ? strdup(home) : strdup("/");
    if (sh->home_dir == NULL)
        return ERROR;
    sh->current_dir = getcwd(NULL, 0);
    if (sh->current_dir == NULL)
        return ERROR;
    sh->previous_dir = strdup(sh->current_dir);
    if (sh->previous_dir == NULL)
        return ERROR;
    return SUCCESS;
}

static int init_shell_components(shell_data_t *sh)
{
    sh->vars = init_var_list();
    if (sh->vars == NULL)
        return ERROR;
    sh->aliases = init_alias_list();
    if (sh->aliases == NULL)
        return ERROR;
    sh->term = init_terminal();
    if (sh->term == NULL)
        return ERROR;
    sh->history = init_history();
    if (sh->history == NULL)
        return ERROR;
    load_history(sh->history);
    return SUCCESS;
}

int initialize_shell(char **environ)
{
    shell_data_t *sh = get_shell_instance();

    if (sh == NULL)
        return ERROR;
    if (init_shell_env(sh, environ) != SUCCESS)
        return ERROR;
    if (init_shell_dirs(sh) != SUCCESS)
        return ERROR;
    if (init_shell_components(sh) != SUCCESS)
        return ERROR;
    handle_signals();
    return SUCCESS;
}

static void free_shell_components(shell_data_t *sh)
{
    save_history(sh->history);
    free_history(sh->history);
    free_terminal(sh->term);
    free_env_list(sh->env);
    free_var_list(sh->vars);
    free_alias_list(sh->aliases);
}

static void free_shell_paths(shell_data_t *sh)
{
    free(sh->current_dir);
    free(sh->previous_dir);
    free(sh->home_dir);
    free(sh->input_buffer);
}

int cleanup_shell(void)
{
    shell_data_t *sh = get_shell_instance();
    int exit_code;

    if (sh == NULL)
        return ERROR;
    exit_code = sh->exit_code;
    free_shell_components(sh);
    free_shell_paths(sh);
    free(sh);
    return exit_code;
}
