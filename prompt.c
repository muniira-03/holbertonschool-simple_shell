#include "shell.h"
#include <stdio.h>

/**
 * display_prompt - Displays shell prompt only in interactive mode
 * @interactive: Flag for interactive mode
 */
void display_prompt(int interactive)
{
	if (interactive)
	printf("$ ");
	fflush(stdout);
}
