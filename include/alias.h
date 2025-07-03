/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Header file
*/

#ifndef ALIAS_H
    #define ALIAS_H

    #include "types.h"

typedef struct alias_node_s {
    char *name;
    char *value;
    struct alias_node_s *next;
} alias_node_t;

typedef struct alias_list_s {
    alias_node_t *head;
    int size;
} alias_list_t;

alias_list_t *init_alias_list(void);

bool remove_alias(alias_list_t *list, const char *name);
char **expand_aliases(alias_list_t *list, char **args);
status_t builtin_alias(char **args);
status_t builtin_unalias(char **args);
int add_alias(alias_list_t *list, const char *name, const char *value);
void print_alias_list(alias_list_t *list);
int check_quote_balance(const char *value);
int is_quotes(char *value);
void remove_quotes(char **value);
int parse_alias(char *arg, char **name, char **value);
const char *get_alias(alias_list_t *list, const char *key);

#endif
