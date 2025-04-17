#include "shell.h"

/**
 * read_input - Reads input from stdin using read()
 * Return: Input string or NULL on EOF/error
 */
char *read_input(void)
{
static char buffer[MAX_INPUT];
ssize_t bytes_read;
char *pos = buffer;
size_t remaining = MAX_INPUT - 1;

while (1)
{
bytes_read = read(STDIN_FILENO, pos, remaining);
if (bytes_read <= 0)
break;
pos += bytes_read;
remaining -= bytes_read;
if (*(pos - 1) == '\n')
break;
}

if (bytes_read <= 0 && pos == buffer)
return (NULL);

*pos = '\0';
return (buffer);
}
