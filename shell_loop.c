#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM    0
#define CMD_OR      1
#define CMD_AND     2
#define CMD_CHAIN   3

/* for convert_number() */
#define CONVERT_LOWERCASE   1
#define CONVERT_UNSIGNED    2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE   ".simple_shell_history"
#define HIST_MAX    4096

extern char **environ;

/* Struct for linked list nodes */
typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;

typedef struct passinfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environ;
    int env_changed;
    int status;

    char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
    int cmd_buf_type; /* CMD_type ||, &&, ; */
    int readfd;
    int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

typedef struct builtin
{
    char *type;
    int (*func)(info_t *);
} builtin_table;

/* Function prototypes */

int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);
char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int bfree(void **ptr);
int _strlen(char *str);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *str, const char *prefix);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);
ssize_t get_input(info_t *info);
int _getline(info_t *info, char **lineptr, size_t *n);
void sigintHandler(int sig_num);
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int env_free);
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *name);
int _setenv(info_t *info, char *name, char *value);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);

size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);
int _erratoi(char *s);
void print_error(info_t *info, char *msg);
int print_d(int d, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *str);
int is_chain(info_t *info, char *cmd, size_t *i);
void check_chain(info_t *info, char *cmd, size_t *i, size_t j, size_t k);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **str, char *token);

int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);
int _myhistory(info_t *info);
int _myalias(info_t *info);
int _myenv(info_t *info);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);

#endif
