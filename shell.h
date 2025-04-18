#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

/* Prototypes */
void display_prompt(int interactive);
char *read_input(void);
int parse_input(char *input, char *args[]);
int execute_command(char *args[], char **env);
int handle_builtins(char **args);

#endif
