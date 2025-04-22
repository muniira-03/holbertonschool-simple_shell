#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

/* Function declarations */
int _getline(char *buffer, int size);
char *_getenv(const char *name);
int parse_input(char *input, char **args);
void execute_command(char **args, char **env);
char *find_command_path(char *command);
int is_builtin(char **args);
void split_commands(char *input, char **env);
extern char **environ;
void free_args(char **args);
#endif /* SHELL_H */
