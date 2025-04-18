#include "shell.h"

/**
 * split_commands - Handles multiple commands
 * @input: Input string with commands
 * @env: Environment variables
 */
void split_commands(char *input, char **env)
{
char *args[MAX_ARGS];
char *start = input;

while (*input)
{
if (*input == '\n')
{
*input = '\0';
if (parse_input(start, args) > 0)
execute_command(args, env);
start = input + 1;
}
input++;
}

if (*start)
{
if (parse_input(start, args) > 0)
execute_command(args, env);
}
}
