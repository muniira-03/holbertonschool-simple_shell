#include "shell.h"

/**
* find_command_path - Finds command in PATH
* @command: Command to find
* @env: Environment variables
* Return: Full path if found, NULL otherwise
*/
char *find_command_path(char *command, char **env)
{
	char *path, *path_copy, *dir;
	struct stat st;

	if (_strchr(command, '/')) /* If command contains '/', check directly */
	{
		if (stat(command, &st) == 0)
		return (strdup(command));
		return (NULL);
	}
	path = _getenv("PATH", env);
	if (!path)
	return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
	return (NULL);

	dir = _strtok(path_copy, ":");
	while (dir)
	{
		char *full_path = malloc(_strlen(dir) + _strlen(command) + 2);

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
		dir = _strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}


/**
* _getenv - Custom getenv implementation
* @name: Variable name to find
* @env: Environment variables array
* Return: Value of variable or NULL if not found
*/
char *_getenv(const char *name, char **env)
{
	size_t name_len = _strlen(name);
	int i;

	if (!name || !env)
	return (NULL);

	for (i = 0; env[i]; i++)
	{
	if (_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
	{
		return (&env[i][name_len + 1]);
	}
	}
	return (NULL);
}
