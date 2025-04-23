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

/*
 * execute_command - Executes a single command
 * @args: Array of command and arguments
 * Return: Status code
 */

int execute_command(char **args, int *last_status, int *cmd_count)
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
    {/*new*/
/* Check if PATH is empty */
        char *path = getenv("PATH");
        if (path == NULL || path[0] == '\0')
        {
            fprintf(stderr, "./hsh: %d: %s: not found\n", *cmd_count, args[0]);
            exit(127);
        }
    
	    
        execvp(args[0], args);
        fprintf(stderr, "./hsh: %d: %s: not found\n", *cmd_count, args[0]);
        exit(127);
    }
    else if (pid > 0)
    {
       (*cmd_count)++;
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
