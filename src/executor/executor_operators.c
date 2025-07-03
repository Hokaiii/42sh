/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** logical operators exec
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../../include/shell.h"

status_t execute_and(ast_node_t *node)
{
    status_t left_status;

    if (node == NULL || node->left == NULL || node->right == NULL)
        return ERROR;
    left_status = execute_node(node->left);
    if (left_status == SUCCESS)
        return execute_node(node->right);
    return left_status;
}

status_t execute_or(ast_node_t *node)
{
    status_t left_status;

    if (node == NULL || node->left == NULL || node->right == NULL)
        return ERROR;
    left_status = execute_node(node->left);
    if (left_status != SUCCESS)
        return execute_node(node->right);
    return left_status;
}

status_t execute_semicolon(ast_node_t *node)
{
    status_t status;

    if (node == NULL || node->left == NULL)
        return ERROR;
    status = execute_node(node->left);
    if (node->right != NULL)
        status = execute_node(node->right);
    return status;
}

status_t execute_background(ast_node_t *node)
{
    pid_t pid;

    if (node == NULL || node->left == NULL)
        return ERROR;
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return ERROR;
    }
    if (pid == 0) {
        setpgid(0, 0);
        exit(execute_node(node->left));
    }
    printf("[%d] %d\n", 1, pid);
    if (node->right != NULL)
        return execute_node(node->right);
    return SUCCESS;
}
