# include <string.h>

# define BUFFER 1024

char *get_output(char command[])
{
	char *returning_output = malloc(BUFFER);
	FILE *output;
	char string[BUFFER];

	output = popen(command, "r");

	if (output == NULL)
	{
		returning_output = "ERROR WHILE OPENING THE PIPE!";
	}
	else
	{
		fgets(returning_output, BUFFER-1, output);
	}

	returning_output[strlen(returning_output)-1] = 0;

	return returning_output;
}
