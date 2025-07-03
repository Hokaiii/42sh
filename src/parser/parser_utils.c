/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parser utils
*/

#include <stdlib.h>
#include <string.h>
#include "../../include/shell.h"

static ast_t *initialize_ast(void)
{
    ast_t *ast = malloc(sizeof(ast_t));

    if (ast == NULL)
        return NULL;
    ast->error = ERROR_NONE;
    return ast;
}

static bool are_tokens_invalid(token_list_t *tokens)
{
    return (tokens == NULL || tokens->head == NULL ||
        tokens->head->type == TOKEN_EOF);
}

ast_t *parse_tokens(token_list_t *tokens)
{
    ast_t *ast = initialize_ast();

    if (ast == NULL)
        return NULL;
    if (are_tokens_invalid(tokens)) {
        ast->root = NULL;
        return ast;
    }
    ast->root = parse_list(tokens);
    if (ast->root == NULL) {
        ast->error = ERROR_SYNTAX;
        return ast;
    }
    return ast;
}

static char **realloc_args(char **args, int arg_count)
{
    args = realloc(args, sizeof(char *) * (arg_count + 2));
    return args;
}

static char **tokenize_command(char *cmd_copy)
{
    char **args = NULL;
    int arg_count = 0;
    char *token;
    char *saveptr;

    token = strtok_r(cmd_copy, " \t\n", &saveptr);
    while (token != NULL) {
        args = realloc_args(args, arg_count);
        if (args == NULL) {
            free(cmd_copy);
            return NULL;
        }
        args[arg_count] = strdup(token);
        arg_count++;
        token = strtok_r(NULL, " \t\n", &saveptr);
    }
    if (args != NULL)
        args[arg_count] = NULL;
    return args;
}

char **split_command(char *cmd)
{
    char **args;
    char *cmd_copy;

    if (cmd == NULL)
        return NULL;
    cmd_copy = strdup(cmd);
    if (cmd_copy == NULL)
        return NULL;
    args = tokenize_command(cmd_copy);
    free(cmd_copy);
    return args;
}
