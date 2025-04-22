#include "shell.h"

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
            if (write(STDOUT_FILENO, "$ ", 2) == -1)
                perror("write");

        read_bytes = _getline(input, MAX_INPUT);
        if (read_bytes == -1)  /*/ EOF or error*/
            break;
        else if (read_bytes == 0)  /* Empty line*/
            continue;

        /*Ensure input is null-terminated*/
        if (read_bytes >= MAX_INPUT)
            input[MAX_INPUT - 1] = '\0';
        else
            input[read_bytes] = '\0';

        /* Tokenization with safeguards*/
        token = _strtok(input, " \t\n");
        for (i = 0; token != NULL && i < MAX_ARGS - 1; i++)
        {
            args[i] = token;
            token = _strtok(NULL, " \t\n");
        }
        args[i] = NULL;  /* Ensure NULL termination*/

        if (args[0] == NULL)  /* No command found*/
            continue;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            continue;
        }

        if (pid == 0)  /*Child process*/
        {
            if (execvp(args[0], args) == -1)
            {
                perror(args[0]);
                exit(EXIT_FAILURE);
            }
        }
        else  /*Parent process*/
        {
            waitpid(pid, &status, 0);
        }
    }

    return (0);
}
