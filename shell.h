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


extern char **environ;

ssize_t _getline(char *line, size_t size);
char *_strtok(char *str, const char *delim);
#endif
