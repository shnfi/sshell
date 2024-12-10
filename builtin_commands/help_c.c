#include <string.h>

void help_c(char str[], char username[], int *al)
{
	printw("\n\n");

	char *c = malloc(15);

	for (int i = 5; i < strlen(str) && str[i] != ' '; i++)
	{
		c[strlen(c)] = str[i];
	}

	if (strlen(c) == 0)
	{
		printw(" * Please use the 'help help' command to find the 'help' command's syntax.");
		*al += 1;
	}

	if (strcmp(c, "help") == 0)
	{
		printw("Usage: help [command]\nShows the help screen of any command.\n");
		*al += 2;
	}
	else if (strcmp(c, "saywithsmile") == 0)
	{
		printw("Usage: saywithsmile [sentence]\nPrints your sentence with a smiling face.\n");
		*al += 2;
	}
	else if (strcmp(c, "psetting") == 0)
	{
		printw("Usage: psetting [setting]\nCustomizes your prompt.\n\n   -c         shows the clock on prompt\n   -d         shows the date on prompt\n   -s         uses square brackets for prompt\n   -r         uses round brackets for prompt\n   -1         changes the style of prompt to style 1\n");
		*al += 8;
	}
}
