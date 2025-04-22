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
 */
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

/**
 * execute_command - Executes a single command
 * @args: Array of command and arguments
 * Return: Status code
 */
int execute_command(char **args)
{
    pid_t pid;
    int status;

    if (_strcmp(args[0], "exit") == 0)
        handle_exit(args);

    pid = fork();
    if (pid == 0)
    {
        execvp(args[0], args);
        perror(args[0]);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    }
    else
    {
        perror("fork");
        return 1;
    }
}

