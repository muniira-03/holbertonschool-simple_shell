#include "shell.h"

/**
 * parse_input - Splits input into arguments
 * @input: User input string
 * @args: Array to store arguments
 *
 * Return: Number of arguments
 */
int parse_input(char *input, char *args[])
{
	int i = 0;
	char *token = strtok(input, " \t\n");

	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (i);
}
