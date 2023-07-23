#ifndef MAIN_H
#define MAIN_H

#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *d;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *com);
char *fill_path(char *p);
list_t *get_path(char *p);
void print_prompt(int s);
int exe_command(char **arg, char **p);
void free_list(list_t *head);
char *_itoa(int num);

/* Input Helpers */
void split_line(char **l, ssize_t r);
ssize_t get_new_line(char *l);
void check_op(char *l, ssize_t *len);
void handle_variable(char **arg, int *ret_com);
char *get_pid(void);
char *make_env_value(char *b, int l);
char *get_arg(char *l, int *ret_com);
int name_arg(char **arg, char **p, int *ret_com);
int execute_arg(char **arg, char **p, int *ret_com);
int handle_arg(int *ret_com);
int test_arg(char **arg);
void free_mem(char **arg, char **p);
char **replace_aliases(char **args);

/* String functions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_builtin(char *command))(char **args, char **front);
int shellof_exit(char **args, char **front);
int shellof_en(char **args, char __attribute__((__unused__)) **front);
int shellof_geten(char **args, char __attribute__((__unused__)) **front);
int shellof_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellof_cd(char **args, char __attribute__((__unused__)) **front);
int shellof_alias(char **args, char __attribute__((__unused__)) **front);
int shellof_help(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/* Error Handling */
int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* Linkedlist Helpers */
alias_t *add_alias(alias_t **h, char *n, char *v);
void free_alias(alias_t *h);
list_t *add_node_end(list_t **h, char *d);
void free_list(list_t *h);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

int proc_file_commands(char *file_path, int *exe_ret);

/* memeory leaks */
int memfree(void **p);

#endif /* MAIN_H */
