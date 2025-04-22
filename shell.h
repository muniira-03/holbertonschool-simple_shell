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
#define MAX_PATH_LEN 1024

extern char **environ;

int split_input(char *input, char **args);
char *find_command_path(char *command);


#endif
