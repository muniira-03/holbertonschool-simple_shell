#include "shell.h"

/**
 * main - Entry point for the simple shell
 * @argc: Argument count (unused)
 * @argv: Argument vector (unused)
 * @env: Environment variables
 *
 * Return: EXIT_SUCCESS on clean exit
 */
int main(int argc __attribute__((unused)),
	char **argv __attribute__((unused)),
	char **env)
{
	char input[MAX_INPUT];
	char *args[MAX_ARGS];
	int arg_count;

	while (1)
	{
		display_prompt();

		if (fgets(input, MAX_INPUT, stdin) == NULL)
		{
			printf("\n");
			break;
		}

		arg_count = parse_input(input, args);
		if (arg_count == 0)
			continue;

		execute_command(args, env);
	}


	return (EXIT_SUCCESS);
}
