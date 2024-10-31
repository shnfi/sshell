# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <time.h>

# include <ncurses.h>

# include "get_output.h"
# include "builtin_commands/exit_c.h"

# define USERNAME get_output("whoami")
# define MAX_COMMAND_LEN 500
# define ctrl(x) ((x) & 0x1f)

typedef struct
{
	char data[MAX_COMMAND_LEN];
	int len;
} command_s;

int main()
{
	initscr();
	noecho();
	raw();
	scrollok(stdscr, true);
	keypad(stdscr, true);

	int line = 0;
	bool *EXIT = malloc(sizeof(bool));
	*EXIT = false;

	command_s command = { "", 0 };

	do
	{
		time_t t = time(NULL);
  		struct tm tm = *localtime(&t);
  		//printw("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec); // a line for finding the date and time format specifiers (delete me later!)

		mvprintw(line, 0, "[%02d:%02d:%02d]-[%s]~> ", tm.tm_hour, tm.tm_min, tm.tm_sec, USERNAME);
		mvprintw(line, sizeof(USERNAME) + 18, "%s", command.data);
		
		int ch = getch();

		switch (ch)
		{
			case 10 : // 'enter' key
				int additional_line;

				if (strcmp(command.data, "exit") == 0)
				{
					exit_c(EXIT);
				}
				else
				{
					char *returning_output = malloc(BUFFER);
					FILE *output;
					char string[BUFFER];
				
					output = popen(command.data, "r");
		
					if (output == NULL)
					{
						returning_output = "ERROR WHILE OPENING THE PIPE!";
					}
					else
					{
						printw("\n\n");
	
						while(fgets(returning_output, BUFFER-1, output))
						{
							printw("%s", returning_output);
							additional_line += 1;						
						}
					}

					free(returning_output);
				}

				line += additional_line + 3;
				additional_line = 0;
				strcpy(command.data, "");
				command.len = 0;
				memset(command.data, 0, sizeof(command.data));
				break;

			case 263 : // 'backspace' key
				if (command.len > 0)
				{
					mvdelch(line, sizeof(USERNAME) + 18 + command.len - 1);
					command.data[command.len-1] = 0;
					command.len -= 1;
				}

				break;

			case ctrl('q') : // 'ctrl' key + 'q' key
				exit_c(EXIT);
				break;

			case ctrl('d') : // 'ctrl' key + 'q' key
				exit_c(EXIT);
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
	} while (!*EXIT);

	free(EXIT);

	endwin();

	return 0;
}
