#include "shell.h"

/**
 * _getline - Custom input reading
 * @buffer: Storage buffer
 * @size: Buffer size
 * Return: Number of bytes read
 */
int _getline(char *buffer, int size)
{
    int i = 0;
    char c;

    while (i < size - 1 && read(STDIN_FILENO, &c, 1) > 0)
    {
        if (c == '\n')
            break;
        buffer[i++] = c;
    }
    buffer[i] = '\0';
    return (i);
}
