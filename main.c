/*
 * project started at Oct 27, 2024
 *
 * there is no such cool thing in it (maybe it is), but the main goal is
 * to learn new things about operating system and have fun ! 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/sysinfo.h>

#include <ncurses.h>

#include "get_one_word_output.h"
#include "called_command_finder.h"
#include "current_dir_name.h"
#include "trim_extra_spaces.h"

#include "builtin_commands/exit_c.c"
#include "builtin_commands/help_c.c"
#include "builtin_commands/clear_c.c"
#include "builtin_commands/saywithsmile_c.c"
#include "builtin_commands/cd_c.c"
#include "builtin_commands/ls_c.c"
#include "builtin_commands/psetting_c.c"
#include "builtin_commands/pwd_c.c"
#include "builtin_commands/uptime_c.c"
#include "builtin_commands/touch_c.c"
#include "builtin_commands/mkdir_c.c"
#include "builtin_commands/rm_c.c"

#define USERNAME get_output("whoami")
#define MAX_COMMAND_LEN 500
#define IS_CTRL_PRESSED(x) ((x) & 0x1f)
#define CWD getcwd(NULL, 100)

#define MAIN_LINE_BUFFER 250

typedef struct
{
	char data[MAX_COMMAND_LEN];
	unsigned int *len;
} command_s;

int main()
{
	initscr();
	noecho();
	raw();
	scrollok(stdscr, true);
	keypad(stdscr, true);

	unsigned int *line = malloc(500);
	*line = 0;

	bool *EXIT = malloc(sizeof(bool));
	*EXIT = false;

	/*
	 * prompt customization variables 
	 */

	char *clock_or_date = malloc(5);
	clock_or_date = "date";

	char *round_or_square = malloc(7);
	round_or_square = "square";

	/*
	 * declaring the 'command' object
	 */

	command_s command = { "", malloc(MAX_COMMAND_LEN) };

	do
	{
		time_t t = time(NULL);
  		struct tm tm = *localtime(&t);

		if (clock_or_date == "clock")
		{
			/*
			 * this prompt include the current clock
			 */

			if (round_or_square == "round")
			{
				mvprintw(*line, 0, "(%02d:%02d:%02d)-(%s)-(%s)~> ", tm.tm_hour, tm.tm_min, tm.tm_sec, current_dir_name(getcwd(NULL, 100)), USERNAME);
			}
			else if (round_or_square == "square")
			{
				mvprintw(*line, 0, "[%02d:%02d:%02d]-[%s]-[%s]~> ", tm.tm_hour, tm.tm_min, tm.tm_sec, current_dir_name(getcwd(NULL, 100)), USERNAME);
			}

			mvprintw(*line, sizeof(USERNAME) + 18 + strlen(current_dir_name(getcwd(NULL, 100))) + 3, "%s", command.data);
		}
		else if (clock_or_date == "date")
		{
			/*
			 * this prompt include the today's date
			 */
			
			if (round_or_square == "round")
			{
				mvprintw(*line, 0, "(%d-%02d-%02d)-(%s)-(%s)~> ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, current_dir_name(getcwd(NULL, 100)), USERNAME);
			}
			else if (round_or_square == "square")
			{
				mvprintw(*line, 0, "[%d-%02d-%02d]-[%s]-[%s]~> ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, current_dir_name(getcwd(NULL, 100)), USERNAME);
			}

			mvprintw(*line, sizeof(USERNAME) + 20 + strlen(current_dir_name(getcwd(NULL, 100))) + 3, "%s", command.data);
		}
		
		int ch = getch();

		switch (ch)
		{
			case 10 : /* 'enter' key */
				/*
				 * preparing the structs for the window size
				 */

				struct winsize max;
				ioctl(0, TIOCGWINSZ , &max);

				/*
				 * preparing the structs for the system informations
				 */

				struct sysinfo info;
				sysinfo(&info);

				/*
				 * this is a temporary handle for scrolling problem (content overflow problem) 
				 */
				
				if (*line >= max.ws_row - 5) clear_c(line, command.data, command.len);

				unsigned int *additional_line = malloc(sizeof(int));
				*additional_line = 0;

				/*
				 * checking the command for specific commands and running the builtin commands
				 * from the 'builtin_commands' folder
				 */

				if (strcmp(trim_extra_spaces(command.data), "help") == 0) help_c(USERNAME, additional_line);
				else if (strcmp(trim_extra_spaces(command.data), "exit") == 0) exit_c(EXIT);
				else if (strcmp(trim_extra_spaces(command.data), "clear") == 0) clear_c(line, command.data, command.len);
				else if (strcmp(trim_extra_spaces(command.data), "cd") == 0) { chdir("/home/"); chdir(USERNAME); } /* navigating to the home directory shortcut */
				else if (strcmp(called_command_finder(trim_extra_spaces(command.data)), "saywithsmile") == 0) saywithsmile_c(command.data, additional_line);
				else if (strcmp(called_command_finder(trim_extra_spaces(command.data)), "cd") == 0) cd_c(command.data);
				else if (strcmp(called_command_finder(trim_extra_spaces(command.data)), "ls") == 0) ls_c(getcwd(NULL, 100), additional_line, 'n');
				else if (strcmp(trim_extra_spaces(command.data), "ls -a") == 0 || strcmp(trim_extra_spaces(command.data), "ls -la") == 0) ls_c(getcwd(NULL, 100), additional_line, 'a');
				else if (strcmp(called_command_finder(trim_extra_spaces(command.data)), "psetting") == 0) psetting_c(command.data, &clock_or_date, &round_or_square);
				else if (strcmp(trim_extra_spaces(command.data), "pwd") == 0) pwd_c(getcwd(NULL, 100), additional_line);
				else if (strcmp(trim_extra_spaces(command.data), "uptime") == 0) uptime_c(info.uptime, additional_line);
				else if (strcmp(called_command_finder(trim_extra_spaces(command.data)), "touch") == 0) touch_c(getcwd(NULL, 100), command.data);
				else if (strcmp(called_command_finder(trim_extra_spaces(command.data)), "mkdir") == 0) mkdir_c(getcwd(NULL, 100), command.data);
				else if (strcmp(called_command_finder(trim_extra_spaces(command.data)), "rm") == 0) rm_c(getcwd(NULL, 100), command.data);
				else
				{
					/*
					 * running the entered command if it was not one of the specific 
					 * commands that we checked in the last few lines 
					 */

					char *returning_output = malloc(MAIN_LINE_BUFFER);
					FILE *output;
				
					output = popen(command.data, "r");
		
					if (output == NULL)
					{
						returning_output = "ERROR WHILE OPENING THE PIPE!";
					}
					else
					{
						printw("\n\n");
	
						while(fgets(returning_output, MAIN_LINE_BUFFER - 1, output))
						{
							/*
							 * 'additional_line' variable's purpose is to know how many lines should be
							 * added to the 'line' variable for each line of the command outupt
							 */
							
							printw("%s", returning_output);
							*additional_line += 1;
						}
					}

					free(returning_output);
				}

				/*
				 * if command was not equal to '', this will add 2 lines for the better space between output and the next prompt
				 */

				if (*command.len != 0) *line += 2;

				/*
				 * resetting command struct and adding to the 'line' variable cuz user goes down one row
				 */

				*line += *additional_line + 1;
				*additional_line = 0;
				*command.len = 0;

				free(additional_line);
				memset(command.data, 0, sizeof(command.data));

				break;

			case 263 : /* 'backspace' key */
				if (*command.len > 0)
				{
					if (clock_or_date == "clock")
					{
						mvdelch(*line, sizeof(USERNAME) + 18 + *command.len - 1 + strlen(current_dir_name(getcwd(NULL, 100))) + 3);
					}
					else if (clock_or_date == "date")
					{
						mvdelch(*line, sizeof(USERNAME) + 20 + *command.len - 1 + strlen(current_dir_name(getcwd(NULL, 100))) + 3);
					}
					command.data[*command.len-1] = 0;
					*command.len -= 1;
				}
				else beep();

				break;

			case IS_CTRL_PRESSED('c') : /* 'ctrl' key + 'c' key */
				/*
				 * skipping the current prompt and reseting the command
				 */

				*line += 1;
				memset(command.data, 0, sizeof(command.data));
				*command.len = 0;

				break;

			case IS_CTRL_PRESSED('q') : /* 'ctrl' key + 'q' key */
			case IS_CTRL_PRESSED('d') : /* 'ctrl' key + 'q' key */
				exit_c(EXIT);

				break;

			case IS_CTRL_PRESSED('\b') :
				beep();

				break;

			case 9 : /* 'tab' key */
			case 27 : /* 'esc' key */
			case 265 ... 276 : /* functional keys */
			case 258 ... 261 : /* arrow keys */
				beep();
				
				break;

			default : 
				/* mvprintw(1, 100, "%d", ch); */ /* a line for finding the code of keys (delete me later!) */

				/*
				 * adding the clicked char to the command.data string
				 */

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
