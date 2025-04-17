#include "shell.h"

/**
 * execute_command - Executes command with arguments
 * @args: Array of command and arguments
 * @env: Environment variables
 *
 * Return: 1 on success, 0 on failure
 */
int execute_command(char *args[], char **env)
{
pid_t pid;

	if (args[0] == NULL)
	return (1);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}

	if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}

}
