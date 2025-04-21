#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

extern char **environ;

/* Function prototypes */
char **split_string(char *str, char *delim);
char **parse_path_directories(void);
char *find_command_path(char *command);
void execute_command(char **args);

/* Helper function to split strings */
char **split_string(char *str, char *delim) {
    char **tokens = malloc(MAX_ARGS * sizeof(char *));
    char *token;
    int i = 0;

    if (!tokens) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(str, delim);
    while (token != NULL && i < MAX_ARGS - 1) {
        tokens[i] = strdup(token);
        if (!tokens[i]) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        i++;
        token = strtok(NULL, delim);
    }
    tokens[i] = NULL;
    return tokens;
}

/* Function to split PATH into directories */
char **parse_path_directories(void) {
    char *path = getenv("PATH");
    if (!path) return NULL;
    
    return split_string(path, ":");
}

/* Function to find full path of command */
char *find_command_path(char *command) {
    struct stat st;
    char **path_dirs = parse_path_directories();
    char *full_path = NULL;
    int i, j;  /* Declare all loop variables at the start */

    /* If command contains '/', treat as path */
    if (strchr(command, '/') != NULL) {
        if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
            return strdup(command);
        return NULL;
    }

    /* Search in PATH directories */
    if (path_dirs) {
        for (i = 0; path_dirs[i] != NULL; i++) {
            full_path = malloc(strlen(path_dirs[i]) + strlen(command) + 2);
            if (!full_path) {
                perror("malloc");
                continue;
            }
            sprintf(full_path, "%s/%s", path_dirs[i], command);
            
            if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR)) {
                /* Free path directories before returning */
                for (j = 0; path_dirs[j] != NULL; j++) {
                    free(path_dirs[j]);
                }
                free(path_dirs);
                return full_path;
            }
            free(full_path);
        }
        /* Free path directories */
        for (i = 0; path_dirs[i] != NULL; i++) {
            free(path_dirs[i]);
        }
        free(path_dirs);
    }
    
    return NULL;
}

/* Execute command */
void execute_command(char **args) {
    pid_t pid;
    int status;
    char *full_path;

    if (args[0] == NULL) return;

    full_path = find_command_path(args[0]);
    if (!full_path) {
        fprintf(stderr, "%s: command not found\n", args[0]);
        return;
    }

    pid = fork();
    if (pid == 0) {
        /* Child process */
        if (execve(full_path, args, environ) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror("fork");
    } else {
        /* Parent process */
        waitpid(pid, &status, 0);
    }

    free(full_path);
}

int main(void) {
    char input[MAX_INPUT];
    char **args;
    int i;

    while (1) {
        printf("$ ");
        fflush(stdout);
        
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            printf("\n");
            break;
        }

        /* Remove newline */
        input[strcspn(input, "\n")] = 0;

        /* Skip empty input */
        if (strlen(input) == 0) continue;

        args = split_string(input, " ");
        execute_command(args);
        
        /* Free allocated memory for args */
        for (i = 0; args[i] != NULL; i++) {
            free(args[i]);
        }
        free(args);
    }

    return 0;
}
