/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Header file
*/

#ifndef PARSER_H
    #define PARSER_H

    #include "types.h"

typedef struct token_s {
    token_type_t type;
    char *value;
    struct token_s *next;
} token_t;

typedef struct token_list_s {
    token_t *head;
    token_t *current;
    int size;
} token_list_t;

typedef struct ast_node_s {
    node_type_t type;
    char **args;
    char *redirect_file;
    struct ast_node_s *left;
    struct ast_node_s *right;
} ast_node_t;

typedef struct ast_s {
    ast_node_t *root;
    error_type_t error;
} ast_t;

token_list_t *init_token_list(void);
void add_token(token_list_t *list, token_type_t type, char *value);
void free_token_list(token_list_t *list);

token_list_t *tokenize_input(char *input);
ast_t *parse_tokens(token_list_t *tokens);
void free_ast(ast_t *ast);
void free_ast_node(ast_node_t *node);

ast_node_t *create_command_node(char **args);
ast_node_t *create_operator_node(node_type_t type,
    ast_node_t *left, ast_node_t *right);
ast_node_t *create_redirect_node(node_type_t type,
    ast_node_t *command, char *file);

void advance_token(token_list_t *tokens);
token_t *get_token(token_list_t *tokens, int offset);
bool expect_token(token_list_t *tokens, token_type_t type);
char **collect_command_args(token_list_t *tokens);

ast_node_t *parse_command(token_list_t *tokens);
ast_node_t *parse_pipeline(token_list_t *tokens);
ast_node_t *parse_list(token_list_t *tokens);

char **split_command(char *cmd);
void expand_variables(char **args);
void handle_globbing(char ***args);

#endif
