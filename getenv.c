#include "shell.h"

/**
 * _getenv - Custom getenv implementation
 * @name: Environment variable name
 * Return: Value or NULL if not found
 */
char *_getenv(const char *name)
{
    extern char **environ;
    char *env_var;
    unsigned int i = 0;

    while (environ[i])
    {
        env_var = environ[i];
        if (strncmp(name, env_var, strlen(name)) == 0 && 
            env_var[strlen(name)] == '=')
            return (&env_var[strlen(name) + 1]);
        i++;
    }
    return (NULL);
}
