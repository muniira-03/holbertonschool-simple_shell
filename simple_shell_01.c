#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

if (parse_input(input, args) > 0)
execute_command(args, env);
}

return (EXIT_SUCCESS);
}
