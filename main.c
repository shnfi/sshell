# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <time.h>

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
	keypad(stdscr, true);

	int line = 0;
	bool EXIT = false;

	command_s command = { "", 0 };

	do
	{
		time_t t = time(NULL);
  		struct tm tm = *localtime(&t);
  		//printw("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

		mvprintw(line, 0, "[%02d:%02d:%02d] (%s)$ ", tm.tm_hour, tm.tm_min, tm.tm_sec, USERNAME);
		mvprintw(line, sizeof(USERNAME) + 20, "%s", command.data);
		
		int ch = getch();

		switch (ch)
		{
			case 10 : // 'enter' key
				line += 1;
				strcpy(command.data, "");
				command.len = 0;
				memset(command.data, 0, sizeof(command.data));
				break;

			case 263 : // 'backspace' key
				if (command.len > 0)
				{
					mvdelch(line, sizeof(USERNAME) + 20 + command.len - 1);
					command.data[command.len-1] = 0;
					command.len -= 1;
				}

				break;

			case 261 : // 'right arrow' key
				break;

			case 260 : // 'left arrow' key
				break;

			case 258 : // 'down arrow' key
				break;

			case 259 : // 'up arrow' key
				break;

			default : 
				//mvprintw(1, 100, "%d", ch); // a line for finding the code of keys (delete me later!)
				command.data[command.len] = (char) ch;
				command.len += 1;
				break;
		}
		
		refresh();
	} while (!EXIT);

	endwin();

	return 0;
}
