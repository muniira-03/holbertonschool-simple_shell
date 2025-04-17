#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_INPUT 1024

/**
 * display_prompt - Displays the shell prompt ($ )
 */
void display_prompt(void)
{
printf("$ ");
fflush(stdout);
}

/**
 * execute_command - Executes a command in a child process
 * @command: The command to execute
 * @env: Environment variables
 *
 * Return: 1 on success, 0 on failure
 */
int execute_command(char *command, char **env)
{
pid_t pid;
char *args[2];  /* Declare array first */

/* Then assign values */
args[0] = command;
args[1] = NULL;

pid = fork();
if (pid == -1)
{
perror("fork");
return (0);
}

if (pid == 0)
{
if (execve(command, args, env) == -1)
{
perror("./shell");
exit(EXIT_FAILURE);
}
}
else
{
wait(NULL);
}

return (1);
}

/**
 * main - Entry point for the simple shell
 * @argc: Argument count (unused)
 * @argv: Argument vector (unused)
 * @env: Environment variables
 *
 * Return: EXIT_SUCCESS on clean exit
 */
int main(int argc __attribute__((unused)),
char **argv __attribute__((unused)), char **env)
{
char input[MAX_INPUT];
size_t len;

while (1)
{
display_prompt();

if (fgets(input, MAX_INPUT, stdin) == NULL)
{
printf("\n");
break;
}

len = strlen(input);
if (len > 0 && input[len - 1] == '\n')
{
input[len - 1] = '\0';
}

if (strlen(input) == 0)
{
continue;
}

execute_command(input, env);
}

return (EXIT_SUCCESS);
}
