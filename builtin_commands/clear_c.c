#include <string.h>

void clear_c(int *line, char command[], int *len)
{
	*line = 0;
	strcpy(command, "");
	*len = 0;
	clear();
}
