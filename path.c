#include "shell.h"

/**
 * find_command_path - Finds command in PATH
 * @command: Command to find
 * Return: Full path if found, NULL otherwise
 */
char *find_command_path(char *command)
{
    char *path, *path_copy, *dir;
    struct stat st;

    /* If command contains '/', check directly */
    if (strchr(command, '/'))
    {
        if (stat(command, &st) == 0)
            return strdup(command);
        return NULL;
    }

    path = getenv("PATH");
    if (!path)
        return NULL;

    path_copy = strdup(path);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir)
    {
        char *full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path)
        {
            free(path_copy);
            return NULL;
        }

        sprintf(full_path, "%s/%s", dir, command);
        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
