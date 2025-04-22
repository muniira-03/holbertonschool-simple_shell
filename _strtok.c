#include "shell.h"

/**
 * _strtok - Custom strtok implementation
 * @str: String to tokenize
 * @delim: Delimiters
 * Return: Next token
 */
char *_strtok(char *str, const char *delim)
{
    static char *save_ptr;
    char *end;

    if (str)
        save_ptr = str;

    if (!*save_ptr)
        return NULL;

    save_ptr += strspn(save_ptr, delim);
    if (!*save_ptr)
        return NULL;

    end = save_ptr + strcspn(save_ptr, delim);
    if (*end)
        *end++ = '\0';

    str = save_ptr;
    save_ptr = end;
    return str;
}
