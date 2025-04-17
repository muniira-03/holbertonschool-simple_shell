#include "shell.h"

/**
 * main - Simple shell entry point
 * @argc: Argument count (unused)
 * @argv: Argument vector (unused)
 * @env: Environment variables
 * Return: EXIT_SUCCESS on success
 */
int main(int argc __attribute__((unused)),
char **argv __attribute__((unused)),
char **env)
{
char *input;
char *args[MAX_ARGS];
int interactive = isatty(STDIN_FILENO);
char *line;
char *next_line;

while (1)
{
if (interactive)
display_prompt(1);

input = read_input();
if (input == NULL)
{
if (interactive)
printf("\n");
break;
}

line = input;
while (line)
{
next_line = strchr(line, '\n');
if (next_line)
*next_line++ = '\0';

if (parse_input(line, args) > 0)
execute_command(args, env);

line = next_line;
}
}
return (EXIT_SUCCESS);
}
