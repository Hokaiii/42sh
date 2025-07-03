/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** tokenizer implementation
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../../include/shell.h"

static bool is_operator_char(char c)
{
    return (c == '|' || c == '&' || c == ';' || c == '<' || c == '>');
}

static bool is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

static void skip_whitespace(char **current)
{
    while (**current && is_whitespace(**current))
        (*current)++;
}

static void process_word(token_list_t *list, char **current)
{
    char *start = *current;
    int len = 0;
    char *word;

    while (**current && !is_whitespace(**current)
        && !is_operator_char(**current)) {
        (*current)++;
        len++;
    }
    word = malloc(len + 1);
    if (word == NULL)
        return;
    strncpy(word, start, len);
    word[len] = '\0';
    add_token(list, TOKEN_WORD, word);
    free(word);
}

static token_type_t handle_double_char_operator(char first_char,
    char second_char, char *op, char **current)
{
    if ((first_char == '|' && second_char == '|') ||
        (first_char == '&' && second_char == '&')) {
        op[1] = second_char;
        (*current)++;
        return (first_char == '|') ? TOKEN_OR : TOKEN_AND;
    }
    if (first_char == '>' && second_char == '>') {
        op[1] = second_char;
        (*current)++;
        return TOKEN_REDIR_APPEND;
    }
    return TOKEN_UNKNOWN;
}

static token_type_t handle_single_char_operator(char first_char)
{
    switch (first_char) {
        case '>':
            return TOKEN_REDIR_OUT;
        case '<':
            return TOKEN_REDIR_IN;
        case '|':
            return TOKEN_PIPE;
        case ';':
            return TOKEN_SEMICOLON;
        default:
            return TOKEN_UNKNOWN;
    }
}

static token_type_t get_operator_type(char first_char,
    char second_char, char *op, char **current)
{
    token_type_t type = handle_double_char_operator(first_char,
        second_char, op, current);

    if (type != TOKEN_UNKNOWN)
        return type;
    return handle_single_char_operator(first_char);
}

static void process_operator(token_list_t *list, char **current)
{
    token_type_t type;
    char op[3] = {0};

    op[0] = **current;
    (*current)++;
    type = get_operator_type(op[0], **current, op, current);
    if (type != TOKEN_UNKNOWN)
        add_token(list, type, op);
}

void process_token(token_list_t *list, char **current)
{
    skip_whitespace(current);
    if (**current == '\0')
        return;
    if (is_operator_char(**current))
        process_operator(list, current);
    else
        process_word(list, current);
}

token_list_t *tokenize_input(char *input)
{
    token_list_t *list = init_token_list();
    char *current = input;

    if (list == NULL)
        return NULL;
    while (*current)
        process_token(list, &current);
    add_token(list, TOKEN_EOF, NULL);
    return list;
}
