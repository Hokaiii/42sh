/*
** EPITECH PROJECT, 2025
** MINISHELL
** File description:
** my
*/

#ifndef LIB_H
    #define LIB_H

// basic functions
int my_isalpha(char s);
int my_isalpha_str(char *str);

// custom functions
int my_isspace(int chr);
char **split_string(char *str, char delimiter);
char **the_str_to_word_array(char *str, char **divide, char **kdivide);
char *superstrcat(char *chain, ...);
char **arraydup(char **src);
void free_char_2x(char **char2x);
void free_char_3x(char ***char3x);
char **strarraycat(char **array1, char **array2);
char *my_calloc(int size);
int arraylen(char **array);
void bfree(void *thing);
void insert_char(char *str, char c, int pos);
void delete_char(char *str, int pos);
char *file_to_str(char const *file);
int get_file_size(char const *file);
char *file_to_str_wsize(char const *file, int size);
char **get_files_dir(const char *folder);
int count_files(const char *folder);
int is_a_bin(char **path, char *command);
char **get_occurences(char **strings, char *token);
char **get_path_env(char **env);
#endif
