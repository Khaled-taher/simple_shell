#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/**
 * struct list_s - it is a struct
 * @str: str point to certain path
 * @next: pointer to next node
 */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

extern char **environ;

char **get_argv(char *lineptr);
void _builtin_exit(int status);
ssize_t _getline(char **string, size_t *size, FILE *stream);
int findpos(char *str, const char *to_find);
int skip(char *str, const char *to_skip);
int str_len(const char *str);
char *_strtok(char *str, const char *delim);
int get_argv_helper(char *lineptr, int *arg_num, int *char_num);
char **get_command(char *lineptr);
void get_command_helper(char *lineptr, int *command_num, int *error);
int get_command_helper2(char *lineptr, int i);
void helper_error(char **command);
int fork_proc(char **argv, list_t *env);
void _free_arr(char **arr);
char *_strdup(char *str);
char *_strndup(char *str, int n);
int _strlen(const char *s);
int _strcmp(const char *s1, char *s2);
char *str_concat(char *s1, char *s2);
list_t *build_path(char *path);
char *_getenv(list_t *head, char *name);
char **check_path(list_t *env, char **argv, int *status);
char *check_path_helper(list_t *path, char *argv, int *status);
int _setenv(list_t *head, const char *name,
const char *value, int overwrite);
int _setenv_helper1(list_t *head, const char *name, const char *value);
int _setenv_helper2(list_t *current, const char *name, const char *value);
int _unsetenv(list_t *head, const char *name);
void _free_environ(list_t *head);
list_t *_cpy_environ(char **environ);
void _print_environ(list_t *head);
char **list_to_arr(list_t *head);
int is_num(char *str);
int check_builtin(char **argv, list_t *env);
int _atoi(char *s);
int check_name(const char *name);
int check_builtin_helper(char **argv, list_t *env);
int check_builtin_helper2(char **argv, list_t *env);

#endif /*MAIN_H*/

