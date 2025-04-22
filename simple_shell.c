#include "shell.h"

/**
 * main - Simple shell entry point
 * Return: Exit status
 */
int main(void)
{
    char input[MAX_INPUT] = {0};
    char *args[MAX_ARGS] = {NULL};
    pid_t pid;
    int status;
    int interactive = isatty(STDIN_FILENO);
    ssize_t read_bytes;
    char *token;
    int i;

    while (1)
    {
        if (interactive)
            write(STDOUT_FILENO, "$ ", 2);

        read_bytes = read(STDIN_FILENO, input, MAX_INPUT - 1);
        if (read_bytes == -1)
        {
            perror("read");
            break;
        }
        else if (read_bytes == 0) /* EOF */
            break;

        input[read_bytes] = '\0';

        /* Tokenize input */
        token = _strtok(input, " \t\n");
        for (i = 0; token && i < MAX_ARGS - 1; i++)
        {
            args[i] = token;
            token = _strtok(NULL, " \t\n");
        }
        args[i] = NULL;

        if (!args[0]) /* Empty command */
            continue;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            continue;
        }

        if (pid == 0) /* Child */
        {
            execvp(args[0], args);
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
        else /* Parent */
        {
            waitpid(pid, &status, 0);
        }
    }

    return (0);
}
