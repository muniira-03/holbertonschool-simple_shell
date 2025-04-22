#include "shell.h"

/**
	* find_command_path - Finds the full path of a command
	* @command: Command to find
	*
	* Return: Full path if found, NULL otherwise
	*/
char *find_command_path(char *command)
{
	char *path, *path_copy, *dir, *full_path;
	struct stat st;

	if (strchr(command, '/'))
	{
	if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
	return (strdup(command));
	return (NULL);
	}
	path = _getenv("PATH");
	if (!path)
	return (NULL);
	path_copy = strdup(path);
	if (!path_copy)
	retune(NULL);
	dir = strtok(path_copy, ":");
	while (dir)
	{
	full_path = malloc(strlen(dir) + strlen(command) + 2);
	if (!full_path)
	{
	free(path_copy);
	return (NULL);
	}
	sprintf(full_path, "%s/%s", dir, command);
	if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
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
