#include "shell.h"

/**
 * read_input - Reads input from stdin using read()
 * Return: Input string or NULL on EOF/error
 */
char *read_input(void)
{
static char buffer[MAX_INPUT];
ssize_t bytes_read = read(STDIN_FILENO, buffer, MAX_INPUT - 1);

if (bytes_read <= 0)
return (NULL);

buffer[bytes_read] = '\0';
return (buffer);
}
