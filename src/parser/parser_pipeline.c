/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** pipeline parsing
*/

#include <stdlib.h>
#include "../../include/shell.h"

ast_node_t *parse_pipeline(token_list_t *tokens)
{
    ast_node_t *left = parse_command(tokens);
    ast_node_t *right;

    if (left == NULL)
        return NULL;
    if (tokens->head != NULL && tokens->head->type == TOKEN_PIPE) {
        advance_token(tokens);
        right = parse_pipeline(tokens);
        if (right == NULL) {
            free_ast_node(left);
            return NULL;
        }
        return create_operator_node(NODE_PIPE, left, right);
    }
    return left;
}
