#include "shell.h"

/**
 * parse_input - Parses input into arguments
 * @input: Input string
 * @args: Array to store arguments
 *
 * Return: Number of arguments parsed
 */
int parse_input(char *input, char **args)
{
	char *token;
	int i = 0;

	token = strtok(input, " ");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	return (i);
}
