#include "shell.h"

/**
	* execute_command - Executes a command with arguments
	* @args: Array of command and arguments
	* @env: Environment variables
	*
	* Return: void
	*/
void execute_command(char **args, char **env)
{
	pid_t pid;
	int status;
	char *full_path;

	if (!args[0])
	return;

	full_path = find_command_path(args[0]);
	if (!full_path)
	{
	fprintf(stderr, "%s: command not found\n", args[0]);
	fflush(stderr);
	return;
	}

	pid = fork();
	if (pid == 0)
	{
	execve(full_path, args, env);
	perror("hsh");
	free(full_path);
	exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
	perror("hsh");
	}
	else
	{
	waitpid(pid, &status, 0);
	}

	free(full_path);
}
