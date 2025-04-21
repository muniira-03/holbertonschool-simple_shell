#include "shell.h"

void execute_command(char **args, char **env)
{
    pid_t pid;
    int status;
    
    if (!args[0]) {
        return;
    }
    
    pid = fork();
    if (pid == 0) {
        /* Child process */
        execve(args[0], args, env);
        perror("hsh");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("hsh");
    } else {
        /* Parent process */
        waitpid(pid, &status, 0);
    }
}
