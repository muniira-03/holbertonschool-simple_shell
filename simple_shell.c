#include "shell.h"

/**
 * main - Simple shell with proper command processing
 * Return: Exit status
 */
int main(void)
{
    char input[MAX_INPUT] = {0};
    char *commands[MAX_INPUT/2 + 1] = {NULL};
    char *args[MAX_ARGS] = {NULL};
    int interactive = isatty(STDIN_FILENO);
    ssize_t read_bytes;
    int i, j, cmd_count;
    char *cmd_token, *arg_token;

    while (1)
    {
        if (interactive)
            write(STDOUT_FILENO, "$ ", 2);

        read_bytes = read(STDIN_FILENO, input, MAX_INPUT - 1);
        if (read_bytes <= 0)
            break;

        input[read_bytes] = '\0';
/* Split into commands by newline */
        char *cmd = _strtok(input, "\n");
        while (cmd)
        {
            /* Tokenize command */
            int i = 0;
            char *arg = _strtok(cmd, " \t");
            while (arg && i < MAX_ARGS - 1)
            {
                args[i++] = arg;
                arg = _strtok(NULL, " \t");
            }
            args[i] = NULL;

            if (args[0])
            {
                if (_strcmp(args[0], "exit") == 0)
                    handle_exit(args, last_status);
                
                last_status = execute_command(args);
            }

            cmd = _strtok(NULL, "\n");
        }
    }

    return last_status;
}
