#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * find_command_path - Finds the full path of a command
 * @command: The command to find
 * Return: Full path if found, NULL otherwise
 */
char *find_command_path(char *command)
{
    char *path = getenv("PATH");
    char *path_copy, *dir, *full_path;
    int command_len, dir_len;
    struct stat st;

    if (!path)
        return (NULL);

    if (strchr(command, '/') != NULL)
    {
        if (stat(command, &st) == 0)
            return (strdup(command));
        return (NULL);
    }

    path_copy = strdup(path);
    if (!path_copy)
        return (NULL);

    command_len = strlen(command);
    dir = strtok(path_copy, ":");

    while (dir)
    {
        dir_len = strlen(dir);
        full_path = malloc(dir_len + command_len + 2);
        if (!full_path)
        {
            free(path_copy);
            return (NULL);
        }

        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, command);

        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return (full_path);
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}
