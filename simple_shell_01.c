#include "shell.h"

/**
 * main - Simple shell entry point
 *
 * Return: 0 on success
 */
int main(void)
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    extern char **environ;
    int interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (interactive)
            write(STDOUT_FILENO, "$ ", 2);

        if (_getline(input, MAX_INPUT) == -1)
            break;

        if (parse_input(input, args) > 0)
            execute_command(args, environ);
    }
    return (0);
}
