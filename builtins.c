#include "shell.h"

/**
 * handle_builtins - Handles built-in commands
 * @args: Command arguments
 * Return: 1 if builtin handled, 0 otherwise
 */
int handle_builtins(char **args)
{
if (strcmp(args[0], "env") == 0)
{
exit(EXIT_SUCCESS);
return (1);
}
return (0);
}

