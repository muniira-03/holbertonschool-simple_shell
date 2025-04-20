#include "shell.h"

int main(int argc __attribute__((unused)),
char **argv __attribute__((unused)),
char **env)
{
char *input;
char *args[MAX_ARGS];
int interactive = isatty(STDIN_FILENO);

while (1)
{
if (interactive)
display_prompt(1);

input = read_input();
if (!input)
{
if (interactive)
printf("\n");
break;
}

if (parse_input(input, args) > 0)
{
if (!handle_builtins(args))
execute_command(args, env);
}
}
return (EXIT_SUCCESS);
}
