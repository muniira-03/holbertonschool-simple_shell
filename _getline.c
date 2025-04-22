#include "shell.h"

/**
 * _getline - Custom getline implementation
 * @line: Buffer to store input
 * @size: Size of buffer
 * Return: Number of bytes read
 */
ssize_t _getline(char *line, size_t size)
{
    ssize_t bytes = 0;
    char c;

    while (bytes < (ssize_t)size - 1)
    {
        if (read(STDIN_FILENO, &c, 1) != 1)
            return -1;
        
        if (c == '\n')
            break;
            
        line[bytes++] = c;
    }
    line[bytes] = '\0';
    return bytes;
}

