/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** Header file
*/

#ifndef TYPES_H
    #define TYPES_H

typedef int status_t;
typedef int fd_t;

typedef enum {
    NODE_COMMAND,
    NODE_PIPE,
    NODE_REDIR_IN,
    NODE_REDIR_OUT,
    NODE_REDIR_APPEND,
    NODE_REDIR_HEREDOC,
    NODE_AND,
    NODE_OR,
    NODE_SEMICOLON,
    NODE_BACKGROUND,
    NODE_UNKNOWN
} node_type_t;

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_REDIR_HEREDOC,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_SEMICOLON,
    TOKEN_BACKGROUND,
    TOKEN_EOF,
    TOKEN_UNKNOWN
} token_type_t;

typedef enum {
    ERROR_NONE,
    ERROR_SYNTAX,
    ERROR_COMMAND_NOT_FOUND,
    ERROR_PERMISSION_DENIED,
    ERROR_AMBIGUOUS_REDIRECT,
    ERROR_MISSING_REDIRECT_TARGET,
    ERROR_PIPE_ERROR,
    ERROR_FORK_ERROR
} error_type_t;

#endif
