#include <string.h>

#define GOWO_BUFFER 25

char *get_output(char command[])
{
	char *returning_output = malloc(GOWO_BUFFER);
	FILE *output;

	memset(returning_output, 0, sizeof(returning_output));

	output = popen(command, "r");

	if (output == NULL)
	{
		return "ERROR";
	}
	else
	{
		fgets(returning_output, GOWO_BUFFER-1, output);
	}

	returning_output[strlen(returning_output)-1] = 0;

	return returning_output;
}
