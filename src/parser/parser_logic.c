/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** logical operators
*/

#include <stdlib.h>
#include "../../include/shell.h"

static bool is_and_or_token(token_t *token)
{
    return token->type == TOKEN_AND || token->type == TOKEN_OR;
}

static bool is_list_token(token_t *token)
{
    return token->type == TOKEN_SEMICOLON || token->type == TOKEN_BACKGROUND;
}

static node_type_t get_node_type(token_t *token)
{
    if (token->type == TOKEN_AND)
        return NODE_AND;
    if (token->type == TOKEN_OR)
        return NODE_OR;
    if (token->type == TOKEN_SEMICOLON)
        return NODE_SEMICOLON;
    if (token->type == TOKEN_BACKGROUND)
        return NODE_BACKGROUND;
    return NODE_UNKNOWN;
}

static ast_node_t *create_operator_node_with_check(node_type_t type,
    ast_node_t *left, ast_node_t *right)
{
    if (right == NULL) {
        free_ast_node(left);
        return NULL;
    }
    return create_operator_node(type, left, right);
}

static ast_node_t *parse_and_or(token_list_t *tokens)
{
    ast_node_t *left = parse_pipeline(tokens);
    ast_node_t *right;
    node_type_t type;

    if (left == NULL)
        return NULL;
    if (tokens->head != NULL && is_and_or_token(tokens->head)) {
        type = get_node_type(tokens->head);
        advance_token(tokens);
        right = parse_and_or(tokens);
        return create_operator_node_with_check(type, left, right);
    }
    return left;
}

ast_node_t *parse_list(token_list_t *tokens)
{
    ast_node_t *left = parse_and_or(tokens);
    ast_node_t *right;
    node_type_t type;

    if (left == NULL)
        return NULL;
    if (tokens->head != NULL && is_list_token(tokens->head)) {
        type = get_node_type(tokens->head);
        advance_token(tokens);
        if (tokens->head != NULL && tokens->head->type != TOKEN_EOF) {
            right = parse_list(tokens);
            return create_operator_node_with_check(type, left, right);
        }
    }
    return left;
}
