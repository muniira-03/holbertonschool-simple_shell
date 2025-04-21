#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * execute_command - Executes command with basic checks
 * @args: Command and arguments
 * @env: Environment variables
 * Return: 1 on success, 0 on failure
 */
int execute_command(char **args, char **env)
{
pid_t pid;
int status;

if (access(args[0], X_OK) == -1)
{
perror(args[0]);
return (0);
}

pid = fork();
if (pid == -1)
{
perror("fork");
return (0);
}

if (pid == 0)
{
execve(args[0], args, env);
perror(args[0]);
exit(EXIT_FAILURE);
}
else
{
waitpid(pid, &status, 0);
}
return (1);
}
