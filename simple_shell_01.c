
#include "shell.h"

/**
	* main - Simple shell entry point
*
	* Return: 0 on success
	*/
/*int main(void)
{
	char input[MAX_INPUT];
	char *args[MAX_ARGS];
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
	if (interactive)
	write(STDOUT_FILENO, "$ ", 2);

	if (_getline(input, MAX_INPUT) == -1)
	break;

	if (input[0] == '\n' || input[0] == '\0')
		continue;

	input[strcspn(input, "\n")] = '\0';

	if (_getline(input, MAX_INPUT) <= 0)
	{
		if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
		break;
	}

	if (parse_input(input, args) > 0)
	execute_command(args, environ);
	}
	return (0);
} i*/

#include "shell.h"

/**
 * main - Simple shell with PATH handling
 * Return: Exit status
 */
int main(void)
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    pid_t pid;
    int status;
    char *full_path;
    int arg_count;
    while (1)
    {
        /* Display prompt */
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "$ ", 2);

        /* Read input */
        if (fgets(input, MAX_INPUT, stdin) == NULL)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;  /* Handle EOF (Ctrl+D) */
        }

        /* Skip empty lines */
        if (input[0] == '\n')
            continue;

        /* Split input into arguments */
      
       	arg_count = split_input(input, args);
        if (arg_count == 0)
            continue;

        /* Handle built-in exit command */
        if (strcmp(args[0], "exit") == 0)
            exit(EXIT_SUCCESS);

        /* Find command in PATH */
        full_path = find_command_path(args[0]);
        if (!full_path)
        {
            fprintf(stderr, "%s: command not found\n", args[0]);
            continue;
        }

        /* Replace command with full path */
        args[0] = full_path;

        /* Fork and execute */
        pid = fork();
        if (pid == 0)  /* Child process */
        {
            if (execve(args[0], args, environ) == -1)
            {
                perror(args[0]);
                free(full_path);
                exit(EXIT_FAILURE);
            }
        }
        else if (pid > 0)  /* Parent process */
        {
            waitpid(pid, &status, 0);
            free(full_path);
        }
        else
        {
            perror("fork");
            free(full_path);
        }
    }

    return (0);
}
