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
      int last_status = 0; /*new*/

    while (1)
    {
        if (interactive)
            write(STDOUT_FILENO, "$ ", 2);

        read_bytes = read(STDIN_FILENO, input, MAX_INPUT - 1);
        if (read_bytes <= 0)
            break;

        input[read_bytes] = '\0';

        /* Split into commands (by newline) */
        cmd_count = 0;
        cmd_token = _strtok(input, "\n");
        while (cmd_token && cmd_count < MAX_INPUT/2)
        {
            commands[cmd_count++] = cmd_token;
            cmd_token = _strtok(NULL, "\n");
        }
        commands[cmd_count] = NULL;

        /* Process each command */
        for (i = 0; commands[i]; i++)
        {
            /* Split command into arguments */
            j = 0;
            arg_token = _strtok(commands[i], " \t");
            while (arg_token && j < MAX_ARGS - 1)
            {
                args[j++] = arg_token;
                arg_token = _strtok(NULL, " \t");
            }
            args[j] = NULL;

            if (args[0])
                /*execute_command(args);*/
            execute_command(args, &last_status);
        }
    }

    /*return 0;*/
    return last_status;
}
