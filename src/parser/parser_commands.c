/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** command parsing
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/shell.h"

static ast_node_t *parse_simple_command(token_list_t *tokens)
{
    char **args = collect_command_args(tokens);

    if (args == NULL)
        return NULL;
    return create_command_node(args);
}

static node_type_t get_redirection_type(token_type_t type)
{
    switch (type) {
        case TOKEN_REDIR_IN:
            return NODE_REDIR_IN;
        case TOKEN_REDIR_OUT:
            return NODE_REDIR_OUT;
        case TOKEN_REDIR_APPEND:
            return NODE_REDIR_APPEND;
        default:
            return NODE_REDIR_HEREDOC;
    }
}

static char *duplicate_file_name(token_list_t *tokens, ast_node_t *cmd)
{
    char *file_name;

    if (tokens->head == NULL || tokens->head->type != TOKEN_WORD) {
        fprintf(stderr, "Missing name for redirect.\n");
        free_ast_node(cmd);
        return NULL;
    }
    file_name = strdup(tokens->head->value);
    if (file_name == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        free_ast_node(cmd);
        return NULL;
    }
    advance_token(tokens);
    return file_name;
}

static ast_node_t *parse_redirection(token_list_t *tokens, ast_node_t *cmd)
{
    token_type_t type = tokens->head->type;
    node_type_t node_type;
    char *file_name;
    ast_node_t *redirect_node;

    advance_token(tokens);
    file_name = duplicate_file_name(tokens, cmd);
    if (file_name == NULL)
        return NULL;
    node_type = get_redirection_type(type);
    redirect_node = create_redirect_node(node_type, cmd, file_name);
    free(file_name);
    return redirect_node;
}

static bool is_redirection_token(token_type_t type)
{
    return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT ||
            type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

ast_node_t *parse_command(token_list_t *tokens)
{
    ast_node_t *cmd = parse_simple_command(tokens);

    if (cmd == NULL)
        return NULL;
    while (tokens->head != NULL && is_redirection_token(tokens->head->type)) {
        cmd = parse_redirection(tokens, cmd);
        if (cmd == NULL)
            return NULL;
    }
    return cmd;
}
