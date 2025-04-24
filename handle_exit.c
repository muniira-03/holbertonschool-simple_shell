#include "shell.h"

/**
* _atoi - Custom atoi implementation
* @s: String to convert
* Return: Converted number
*/
int _atoi(char *s)
{
	int res = 0, sign = 1, i = 0;

	if (s[0] == '-')
	{
		sign = -1;
		i++;
	}

	for (; s[i]; i++)
	{
	if (s[i] >= '0' && s[i] <= '9')
		res = res * 10 + (s[i] - '0');
	else
		break;
	}

	return (sign * res);
}



/**
* handle_exit - Handles the exit built-in command
* @args: Command arguments
* @last_status: Status of last executed command
*/
void handle_exit(char **args, int last_status)
{
	int status = last_status;

	if (args[1])
	{
		status = _atoi(args[1]);
	if (status < 0)
	{
		fprintf(stderr, "./hsh: exit: %d: numeric argument required\n", status);
		status = 2;
	}
	}
	exit(status);
}



/**
* execute_command - Executes a single command with arguments
* @args: Array of command and arguments
* @last_status: Pointer to store/retrieve last exit status
* @cmd_count: Pointer to command counter for error messages
* @env: Environment variables
* Return: Exit status of the command
*/
int execute_command(char **args, int *last_status, int *cmd_count, char **env)
{
	pid_t pid;
	int status, i;
	char *full_path;

	if (_strcmp(args[0], "exit") == 0)
	{
		handle_exit(args, *last_status);
		return (*last_status);
	}
	else if (_strcmp(args[0], "env") == 0)
	{
		/* Handle env built-in */
		for (i = 0; env[i] != NULL; i++)
		{
			printf("%s\n", env[i]);
		}
		return (0);
	}
	/* Find command in PATH */
	full_path = find_command_path(args[0], env);
	if (!full_path)
	{
		fprintf(stderr, "./hsh: %d: %s: not found\n", *cmd_count, args[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(full_path, args, env);
		/* If execv returns, it failed */
		free(full_path);
		exit(127);
	}
	else if (pid > 0)
	{
		free(full_path);
		waitpid(pid, &status, 0);
		*last_status = WEXITSTATUS(status);
		return (*last_status);
	}
	else
	{
		free(full_path);
		perror("fork");
		*last_status = 1;
		return (1);
	}
}
