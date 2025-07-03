/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Header file
*/

#ifndef ENV_H
    #define ENV_H

    #include "types.h"

typedef struct env_node_s {
    char *key;
    char *value;
    struct env_node_s *next;
} env_node_t;

typedef struct env_list_s {
    env_node_t *head;
    int size;
} env_list_t;

typedef struct var_node_s {
    char *key;
    char *value;
    bool readonly;
    struct var_node_s *next;
} var_node_t;

typedef struct var_list_s {
    var_node_t *head;
    int size;
} var_list_t;

env_list_t *init_env_list(void);
void add_env_var(env_list_t *list, const char *key, const char *value);
void remove_env_var(env_list_t *list, const char *key);
char *get_env_var(env_list_t *list, const char *key);
void free_env_list(env_list_t *list);
char **env_to_array(env_list_t *list);

var_list_t *init_var_list(void);
void add_var(var_list_t *list, const char *key, const char *value,
    bool readonly);
void remove_var(var_list_t *list, const char *key);
char *get_var(var_list_t *list, const char *key);
void free_var_list(var_list_t *list);

#endif
