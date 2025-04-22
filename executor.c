#include "shell.h"

/**
 * execute_command - Executes a command with arguments
 * @args: Array of command and arguments
 * @env: Environment variables
 *
 * Return: 1 on success, 0 on failure
 */
int execute_command(char **args, char **env)
{
    pid_t pid;
    int status;

    if (args[0] == NULL)
        return (1); /* Empty command */

    /* Handle built-in commands */
    if (strcmp(args[0], "exit") == 0)
        return (shell_exit(args));
    if (strcmp(args[0], "env") == 0)
        return (print_environment(env));

    pid = fork();
    if (pid == -1)
    {
        perror("hsh: fork failed");
        return (1);
    }

    if (pid == 0) /* Child process */
    {
        if (execvp(args[0], args) == -1)
        {
            perror("hsh: execution failed");
            exit(EXIT_FAILURE);
        }
    }
    else /* Parent process */
    {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return (1);
}

/**
 * shell_exit - Handles the exit built-in command
 * @args: Command arguments
 *
 * Return: 0 to terminate shell
 */
int shell_exit(char **args)
{
    int exit_status = 0;

    if (args[1] != NULL)
        exit_status = atoi(args[1]);

    free_args(args);
    exit(exit_status);
}

/**
 * print_environment - Prints the current environment
 * @env: Environment variables
 *
 * Return: Always 1
 */
int print_environment(char **env)
{
    int i = 0;

    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }

    return (1);
}

/**
 * free_args - Frees memory allocated for arguments
 * @args: Array of arguments
 */
void free_args(char **args)
{
    int i = 0;

    if (args == NULL)
        return;

    while (args[i] != NULL)
    {
        free(args[i]);
        i++;
    }
}
