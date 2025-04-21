#include "shell.h"

int parse_input(char *input, char **args)
{
    char *token;
    int i = 0;
    
    token = strtok(input, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    return i; /* Return number of arguments parsed */
}
