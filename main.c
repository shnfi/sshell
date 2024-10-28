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
	noecho();

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
			case 10 : // 'enter' key
				line += 1;
				strcpy(command.data, "");
				command.len = 0;
				memset(command.data, 0, sizeof(command.data));
				break;

			case 127 : // 'backspace' key
				if (command.len > 0)
				{
					mvdelch(line, command.len - 1);
					command.data[command.len-1] = 0;
					command.len -= 1;
				}

				break;

			default : 
				//mvprintw(1, 50, "%d", ch); // a line for finding the code of keys (delete me later!)
				command.data[command.len] = (char) ch;
				command.len += 1;
				break;
		}
		
		refresh();
	} while (!EXIT);

	endwin();

	return 0;
}
