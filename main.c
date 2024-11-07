# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <time.h>
# include <sys/ioctl.h>

# include <ncurses.h>

# include "get_one_word_output.h"
# include "called_command_finder.h"

# include "builtin_commands/exit_c.h"
# include "builtin_commands/help_c.h"
# include "builtin_commands/clear_c.h"
# include "builtin_commands/saywithsmile_c.h"
# include "builtin_commands/cd_c.h"

# define USERNAME get_output("whoami")
# define MAX_COMMAND_LEN 500
# define IS_CTRL_PRESSED(x) ((x) & 0x1f)
# define CWD getcwd(NULL, 100)

typedef struct
{
	char data[MAX_COMMAND_LEN];
	int *len;
} command_s;

int main()
{
	initscr();
	noecho();
	raw();
	scrollok(stdscr, true);
	keypad(stdscr, true);

	int *line = malloc(500);
	*line = 0;

	bool *EXIT = malloc(sizeof(bool));
	*EXIT = false;

	command_s command = { "", malloc(MAX_COMMAND_LEN) };

	do
	{
		time_t t = time(NULL);
  		struct tm tm = *localtime(&t);
  		//printw("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec); // a line for finding the date and time format specifiers (delete me later!)

		mvprintw(*line, 0, "[%02d:%02d:%02d]-[%s]~> ", tm.tm_hour, tm.tm_min, tm.tm_sec, USERNAME);
		mvprintw(*line, sizeof(USERNAME) + 18, "%s", command.data);
		
		int ch = getch();

		switch (ch)
		{
			case 10 : // 'enter' key
				struct winsize max;
				ioctl(0, TIOCGWINSZ , &max);

				if (*line >= max.ws_row - 5) clear_c(line, command.data, command.len); // this is a temporary handle for scrolling problem (content overflow problem) .

				int *additional_line = malloc(sizeof(int));
				*additional_line = 0;

				if (strcmp(command.data, "help") == 0) help_c(USERNAME, additional_line);
				else if (strcmp(command.data, "exit") == 0) exit_c(EXIT);
				else if (strcmp(command.data, "clear") == 0) clear_c(line, command.data, command.len);
				else if (strcmp(called_command_finder(command.data), "saywithsmile") == 0) saywithsmile_c(command.data, additional_line);
				else if (strcmp(called_command_finder(command.data), "cd") == 0) cd_c(command.data);
				else
				{
					char *returning_output = malloc(BUFFER);
					FILE *output;
				
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
							*additional_line += 1;						
						}
					}

					free(returning_output);
				}

				if (*command.len != 0) *line += 2;

				*line += *additional_line + 1;
				*additional_line = 0;
				strcpy(command.data, "");
				*command.len = 0;

				free(additional_line);
				memset(command.data, 0, sizeof(command.data));

				break;

			case 263 : // 'backspace' key
				if (*command.len > 0)
				{
					mvdelch(*line, sizeof(USERNAME) + 18 + *command.len - 1);
					command.data[*command.len-1] = 0;
					*command.len -= 1;
				}

				break;

			case IS_CTRL_PRESSED('c') : // 'ctrl' key + 'c' key
				*line += 1;
				strcpy(command.data, "");
				*command.len = 0;
				break;

			case IS_CTRL_PRESSED('q') : // 'ctrl' key + 'q' key
				exit_c(EXIT);
				break;

			case IS_CTRL_PRESSED('d') : // 'ctrl' key + 'q' key
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
				command.data[*command.len] = (char) ch;
				*command.len += 1;
				break;
		}
		
		refresh();
	} while (!*EXIT);

	free(command.len);
	free(line);
	free(EXIT);

	endwin();

	return 0;
}
