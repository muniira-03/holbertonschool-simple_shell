#include "shell.h"


/**
 * _strlen - Custom strlen implementation
 * @s: String to measure
 * Return: Length of string
 */
size_t _strlen(const char *s)
{
    size_t len = 0;
    while (s && s[len]) len++;
    return len;
}

/**
 * _strchr - Custom strchr implementation
 * @s: String to search
 * @c: Character to find
 * Return: Pointer to character or NULL
 */
char *_strchr(const char *s, int c)
{
    while (s && *s)
    {
        if (*s == c)
            return (char *)s;
        s++;
    }
    return NULL;
}

/**
 * _strtok - Custom strtok implementation without strspn
 * @str: String to tokenize
 * @delim: Delimiters
 * Return: Next token or NULL
 */
char *_strtok(char *str, const char *delim)
{
    static char *save_ptr;
    char *start, *end;

    if (str)
        save_ptr = str;

    if (!save_ptr || !*save_ptr)
        return NULL;

    /* Skip leading delimiters */
    start = save_ptr;
    while (*start)
    {
        if (!_strchr(delim, *start))
            break;
        start++;
    }

    if (!*start)
    {
        save_ptr = start;
        return NULL;
    }

    /* Find end of token */
    end = start;
    while (*end && !_strchr(delim, *end))
        end++;

    if (*end)
    {
        *end = '\0';
        save_ptr = end + 1;
    }
    else
    {
        save_ptr = end;
    }

    return start;
}


/**
 * _strcmp - Custom strcmp implementation
 * @s1: First string
 * @s2: Second string
 * Return: 0 if equal, difference otherwise
 */
int _strcmp(char *s1, char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
