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
char *command;
char *args[MAX_ARGS];
char *saveptr;

	while ((input = read_input()) != NULL)
	{
		command = strtok_r(input, "\n", &saveptr);
			while (command != NULL)
			{
				if (parse_input(command, args) > 0)
				{
					execute_command(args, env);
				}
				command = strtok_r(NULL, "\n", &saveptr);
			}
	}
return (EXIT_SUCCESS);
}
