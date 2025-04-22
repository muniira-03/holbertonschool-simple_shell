#include "shell.h"

/**
 * free_args - Frees memory allocated for arguments array
 * @args: Array of arguments to free
 */
void free_args(char **args)
{
	int i;
    if (!args)
        return;

    for (i = 0; args[i]; i++)
    {
        free(args[i]);
        args[i] = NULL;
    }
}
