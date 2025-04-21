#include "shell.h"

void split_commands(char *input, char **env)
{
    char *start = input;
    char *end;
    char *args[MAX_ARGS];
    int arg_count;
    
    while (*start) {
        /* Find command separator (;) */
        end = strchr(start, ';');
        if (end) {
            *end = '\0';
        }
        
        /* Parse and execute current command */
        arg_count = parse_input(start, args);
        if (arg_count > 0) { /* Compare with integer, not pointer */
            execute_command(args, env);
        }
        
        /* Move to next command */
        if (end) {
            start = end + 1;
            while (*start == ' ') {
                start++; /* Skip spaces */
            }
        } else {
            break;
        }
    }
}
