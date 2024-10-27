# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# include <ncurses.h>

# include "get_output.h"

# define USERNAME get_output("whoami")
# define MAX_COMMAND_LEN 500

typedef struct
{
	char data[MAX_COMMAND_LEN];
	int len;
} command_s;

int main()
{
	initscr();

	int line = 0;
	bool EXIT = false;

	command_s command = { "", 0 };

	do
	{
		mvprintw(line, 0, "(%s)$ ", USERNAME);
		mvprintw(line, sizeof(USERNAME) + 6, "%s", command.data);
		
		int ch = getch();
		switch (ch)
		{
			case 10 :
				line += 1;
				strcpy(command.data, "");
				//command.data = NULL;
				memset(command.data, 0, sizeof(command.data) * command.len);
				break;

			default : 
				command.len += 1;
				command.data[command.len] = (char) ch;
				break;
		}
		
		refresh();
	} while (!EXIT);

	endwin();

	return 0;
}
