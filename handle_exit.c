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

    return sign * res;
}

/**
 * handle_exit - Handles the exit built-in command
 * @args: Command arguments
 * Return: 1 if not exiting, -1 if exiting with error
 *
int handle_exit(char **args)
{
    int status = 0;

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
*/
/**
 * handle_exit - Handles the exit built-in command
 * @args: Command arguments
 * @last_status: Status of last executed command
 */
void handle_exit(char **args, int last_status)
{
    int status = last_status; /* Default to last command's status */

    if (args[1]) /* If exit has argument */
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
 * execute_command - Executes a single command
 * @args: Array of command and arguments
 * Return: Status code
 */
int execute_command(char **args, int *last_status) /*int *last_status is new*/
{
    pid_t pid;
    int status;

    if (_strcmp(args[0], "exit") == 0)
	{
	 	handle_exit(args, *last_status);
        	return *last_status;
	}

    pid = fork();
    if (pid == 0)
    {	
	struct stat st;
	if (stat(args[0], &st) == -1)/*new*/
        {
          fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
            exit(127);
        }


        execvp(args[0], args);
        perror(args[0]);
	exit(127); /* Command not found status */
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
	*last_status = WEXITSTATUS(status);
        return *last_status;
    }
    else
    {
        perror("fork");
	*last_status = 1;
        return 1;
    }
}

