/*
** EPITECH PROJECT, 2025
** B-PSU-200-NCY-2-1-42sh-eren.turkoglu
** File description:
** main
*/

#include "../include/ncurses_fun.h"


static FILE *redirect_output_to_temp(int *saved_stdout_fd
    , int *saved_stderr_fd)
{
    FILE *temp_fp = tmpfile();
    int temp_fd;

    if (!temp_fp)
        return NULL;
    temp_fd = fileno(temp_fp);
    *saved_stdout_fd = dup(fileno(stdout));
    *saved_stderr_fd = dup(fileno(stderr));
    dup2(temp_fd, fileno(stdout));
    dup2(temp_fd, fileno(stderr));
    return temp_fp;
}

static void restore_output(int saved_stdout_fd, int saved_stderr_fd)
{
    fflush(stdout);
    fflush(stderr);
    dup2(saved_stdout_fd, fileno(stdout));
    dup2(saved_stderr_fd, fileno(stderr));
    close(saved_stdout_fd);
    close(saved_stderr_fd);
}

static void display_temp_output_ncurses(FILE *temp_fp)
{
    char buffer[1024];

    rewind(temp_fp);
    printw("\n");
    while (fgets(buffer, sizeof(buffer), temp_fp))
        printw("%s", buffer);
    wrefresh(stdscr);
    fclose(temp_fp);
}

static void handle_token(token_list_t *tokens, shell_data_t *sh)
{
    ast_t *ast;

    if (!tokens)
        return;
    ast = parse_tokens(tokens);
    if (!ast){
        free_token_list(tokens);
        return;
    }
    sh->exit_code = execute_ast(ast);
    free_ast(ast);
    free_token_list(tokens);
    return;
}

int str_to_ast(char *str)
{
    shell_data_t *sh = get_shell_instance();
    token_list_t *tokens;
    FILE *temp_fp = NULL;
    int saved_stdout = -1;
    int saved_stderr = -1;

    temp_fp = redirect_output_to_temp(&saved_stdout, &saved_stderr);
    add_to_nhistory(str);
    tokens = tokenize_input(str);
    handle_token(tokens, sh);
    if (temp_fp) {
        restore_output(saved_stdout, saved_stderr);
        display_temp_output_ncurses(temp_fp);
    }
    if (strcmp(str, "exit") == 0)
        exit(0);
    return RESET_CMD + SHOW_PROMPT;
}
