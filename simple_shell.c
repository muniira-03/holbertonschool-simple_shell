#include "shell.h"

/**
* main - Simple shell with proper command processing
* @argc: Argument count
* @argv: Argument vector
* @env: Environment variables
*
* Return: Exit status
*/

int main(int argc, char **argv, char **env)
{
	char input[MAX_INPUT] = {0}, *commands[MAX_INPUT / 2 + 1] = {NULL};
	char *args[MAX_ARGS] = {NULL}, *cmd_token, *arg_token;
	int interactive = isatty(STDIN_FILENO);
	int i, j, cmd_count, last_status = 0, cmd_counter = 1;
	ssize_t read_bytes;
	(void)argc;
	(void)argv;

	while (1)
	{
	if (interactive)
	write(STDOUT_FILENO, "$ ", 2);
	read_bytes = read(STDIN_FILENO, input, MAX_INPUT - 1);
	if (read_bytes <= 0)
	break;
	input[read_bytes] = '\0';
	cmd_count = 0;/* Split into commands (by newline) */
	cmd_token = _strtok(input, "\n");
	while (cmd_token && cmd_count < MAX_INPUT / 2)
	{
		commands[cmd_count++] = cmd_token;
		cmd_token = _strtok(NULL, "\n");
	}
	commands[cmd_count] = NULL;
	for (i = 0; commands[i]; i++)/* Process each command */
	{	j = 0; /* Split command into arguments */
		arg_token = _strtok(commands[i], " \t");
		while (arg_token && j < MAX_ARGS - 1)
		{
			args[j++] = arg_token;
			arg_token = _strtok(NULL, " \t");
		}
		args[j] = NULL;
		if (args[0])
		{
		last_status = execute_command(args, &last_status, &cmd_counter, env);
		cmd_counter++;
		}}}
	return (last_status);
}
