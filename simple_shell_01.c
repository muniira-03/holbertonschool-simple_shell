#include "shell.h"

/**
 * main - Simple shell entry point
 *
 * Return: 0 on success
 */
int main(void)
{
	char input[MAX_INPUT];
	char *args[MAX_ARGS];
	extern char **environ;

	while (1)
	{
		printf("$");
		fflush(stdout);

		if (!fgets(input, MAX_INPUT, stdin))
		{
			printf("\n");
			break;
		}

		input[strcspn(input, "\n")] = '\0';

		if (parse_input(input, args) > 0)
		{
			execute_command(args, environ);
		}
	}
	return (0);
}
