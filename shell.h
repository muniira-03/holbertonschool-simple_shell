#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>


#define MAX_INPUT 1024
#define MAX_ARGS 64


size_t _strlen(const char *s);
char *_strchr(const char *s, int c);
char *_strtok(char *str, const char *delim);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
int _atoi(char *s);
void handle_exit(char **args, int last_status);
int execute_command(char **args, int *last_status, int *cmd_count, char **env);
char *find_command_path(char *command, char **env);
char *_getenv(const char *name, char **env);


#endif
