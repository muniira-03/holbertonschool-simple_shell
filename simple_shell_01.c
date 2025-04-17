#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - Simple shell entry point
 * @argc: Argument count (unused)
 * @argv: Argument vector (unused)
 * @env: Environment variables
 *
 * Return: EXIT_SUCCESS on success
 */

int main(int argc __attribute__((unused)),
char **argv __attribute__((unused)),
char **env)
{
char *input;
char *args[MAX_ARGS];
int interactive = isatty(STDIN_FILENO);
char *command;
char *newline_pos;

while (1)
{
display_prompt(interactive);
input = read_input();
if (input == NULL)
{
if (interactive)
printf("\n");
break;
}

command = input;
while ((newline_pos = strchr(command, '\n')) != NULL)
{
*newline_pos = '\0';
if (parse_input(command, args) > 0)
execute_command(args, env);
command = newline_pos + 1;
}

if (*command != '\0')
{
if (parse_input(command, args) > 0)
execute_command(args, env);
}
}
return (EXIT_SUCCESS);
}
