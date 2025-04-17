#include "shell.h"

/**
 * read_input - Reads input from stdin using read()
 *
 * Description: Uses the read() system call to get input
 * instead of forbidden functions like fgets().
 * Handles EOF condition (Ctrl+D).
 *
 * Return: Pointer to static buffer containing input,
 *         or NULL on failure/EOF
 */
char *read_input(void)
{
static char buffer[MAX_INPUT];
ssize_t bytes_read;
char *result;

	bytes_read = read(STDIN_FILENO, buffer, MAX_INPUT - 1);
	if (bytes_read == -1)
	{
		perror("read");
		return (NULL);
	}
	else if (bytes_read == 0)
	{
		return (NULL);  /* EOF condition */
	}

	buffer[bytes_read] = '\0';  /* Null-terminate */
	result = buffer;

	/* Remove trailing newline if present */
	if (bytes_read > 0 && buffer[bytes_read - 1] == '\n')
	{
		buffer[bytes_read - 1] = '\0';
	}

	return (result);
}
