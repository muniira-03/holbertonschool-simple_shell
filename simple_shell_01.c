#include "shell.h"

int main(void)
{
    char input[MAX_INPUT];
    /*char *args[MAX_ARGS];*/
    extern char **environ;
    
    while (1) {
        printf("$ ");
        fflush(stdout);
        
        if (!fgets(input, MAX_INPUT, stdin)) {
            printf("\n");
            break;
        }
        
        input[strcspn(input, "\n")] = '\0';
        
        /* Handle multiple commands */
        split_commands(input, environ);
    }
    return 0;
}
