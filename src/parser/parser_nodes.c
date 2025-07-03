/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** ast node creation
*/

#include <stdlib.h>
#include <string.h>
#include "../../include/shell.h"

ast_node_t *create_command_node(char **args)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));

    if (node == NULL)
        return NULL;
    node->type = NODE_COMMAND;
    node->args = args;
    node->redirect_file = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ast_node_t *create_operator_node(node_type_t type, ast_node_t *left,
    ast_node_t *right)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));

    if (node == NULL)
        return NULL;
    node->type = type;
    node->args = NULL;
    node->redirect_file = NULL;
    node->left = left;
    node->right = right;
    return node;
}

ast_node_t *create_redirect_node(node_type_t type, ast_node_t *command,
    char *file)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));

    if (node == NULL)
        return NULL;
    node->type = type;
    node->args = NULL;
    node->redirect_file = (file != NULL) ? strdup(file) : NULL;
    if (file != NULL && node->redirect_file == NULL) {
        free(node);
        return NULL;
    }
    node->left = command;
    node->right = NULL;
    return node;
}

void free_ast_node(ast_node_t *node)
{
    if (node == NULL)
        return;
    if (node->args != NULL) {
        for (int i = 0; node->args[i] != NULL; i++)
            free(node->args[i]);
        free(node->args);
    }
    if (node->redirect_file != NULL) {
        free(node->redirect_file);
    }
    free_ast_node(node->left);
    free_ast_node(node->right);
    free(node);
}

void free_ast(ast_t *ast)
{
    if (ast == NULL)
        return;
    free_ast_node(ast->root);
    free(ast);
}
