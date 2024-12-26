/*
 * project started at Oct 27, 2024
 * project first released at Dec 22, 2024
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

#include "headers/get_one_word_output.h"
#include "headers/called_command_finder.h"
#include "headers/current_dir_name.h"
#include "headers/trim_extra_spaces.h"

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
#include "builtin_commands/echo_c.c"
#include "builtin_commands/search_c.c"
#include "builtin_commands/sizeof_c.c"

#include "command_identification.c"

#define USERNAME get_output("whoami")
#define MAX_COMMAND_LEN 500
#define IS_CTRL_PRESSED(x) ((x) & 0x1f)
#define CWD getcwd(NULL, 250)

#define MAIN_LINE_BUFFER 250

typedef struct
{
	char data[MAX_COMMAND_LEN];
	unsigned int *len;
} command;

int main()
{
	/*
	 * first display settings
	 */
	
	initscr();
	noecho();
	raw();
	scrollok(stdscr, true);
	keypad(stdscr, true);
	start_color();

	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);

	wbkgd(stdscr, COLOR_PAIR(1));

	unsigned int *line = malloc(500);
	*line = 0;

	bool *EXIT = malloc(sizeof(bool));
	*EXIT = false;

	/*
	 * checking if terminal supports colors
	 */

	if (!has_colors() || !can_change_color())
	{
		attron(COLOR_PAIR(3));

		printw("\n [ERROR] Your terminal does not support colors!");
		*line += 3;

		attroff(COLOR_PAIR(3));
	}

	/*
	 * prompt customization variables 
	 */

	char *clock_or_date = malloc(5);
	clock_or_date = "date";

	char *round_or_square = malloc(7);
	round_or_square = "square";

	char *prompt_type = malloc(3);
	prompt_type = "-1"; /* prompt type == -1 means that the prompt is not using each of the custom themes */

	int *using_color_index = malloc(sizeof(int));
	*using_color_index = 1;

	attron(COLOR_PAIR(6));

	printw("\n [ALERT] Current color pair: 1");
	*line += 3;

	attroff(COLOR_PAIR(6));

	/*
	 * declaring the 'command' object
	 */

	command command  = { "", malloc(MAX_COMMAND_LEN) };

	do
	{
		time_t t = time(NULL);
  		struct tm tm = *localtime(&t);

		if (round_or_square == "-1" && clock_or_date != "-1" || round_or_square != "-1" && clock_or_date == "-1")
		{
			round_or_square = "square";
			clock_or_date = "date";
		}

		if (clock_or_date == "clock")
		{
			/*
			 * this prompt include the current clock
			 */

			if (round_or_square == "round")
				mvprintw(*line, 0, "(%02d:%02d:%02d)-(%s)-(%s)~> ", tm.tm_hour, tm.tm_min, tm.tm_sec, current_dir_name(getcwd(NULL, 250)), USERNAME);

			else if (round_or_square == "square")
				mvprintw(*line, 0, "[%02d:%02d:%02d]-[%s]-[%s]~> ", tm.tm_hour, tm.tm_min, tm.tm_sec, current_dir_name(getcwd(NULL, 250)), USERNAME);

			mvprintw(*line, sizeof(USERNAME) + 18 + strlen(current_dir_name(getcwd(NULL, 250))) + 3, "%s", command.data);
		}
		else if (clock_or_date == "date")
		{
			/*
			 * this prompt include the today's date
			 */
			
			if (round_or_square == "round")
				mvprintw(*line, 0, "(%d-%02d-%02d)-(%s)-(%s)~> ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, current_dir_name(getcwd(NULL, 250)), USERNAME);

			else if (round_or_square == "square")
				mvprintw(*line, 0, "[%d-%02d-%02d]-[%s]-[%s]~> ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, current_dir_name(getcwd(NULL, 250)), USERNAME);

			mvprintw(*line, sizeof(USERNAME) + 20 + strlen(current_dir_name(getcwd(NULL, 250))) + 3, "%s", command.data);
		}
		else if (prompt_type == "1")
		{
			/*
			 * the type 1 prompt
			 */

			mvprintw(*line, 0, "%s> ", USERNAME);
			mvprintw(*line, sizeof(USERNAME) + 4, "%s", command.data);
		}
		else if (prompt_type == "2")
		{
			/*
			 * the type 2 prompt
			 */

			mvprintw(*line, 0, "> ");
			mvprintw(*line, 2, "%s", command.data);
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
				
				if (*line >= max.ws_row - 3) 
					clear_c(line, command.data, command.len);

				unsigned int *additional_line = malloc(sizeof(int));
				*additional_line = 0;

				/*
				 * checking the command for specific commands and running the builtin commands
				 * from the 'builtin_commands' folder
				 */

				command_identification(command.data, USERNAME, additional_line, EXIT, line, command.len, &clock_or_date, &round_or_square, MAIN_LINE_BUFFER, info, &prompt_type, using_color_index);

				/*
				 * if command was not equal to '', this will add 2 lines for the better space between output and the next prompt
				 */

				if (*command.len != 0)
					*line += 2;

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
						mvdelch(*line, sizeof(USERNAME) + 18 + *command.len - 1 + strlen(current_dir_name(getcwd(NULL, 250))) + 3);

					else if (clock_or_date == "date")
						mvdelch(*line, sizeof(USERNAME) + 20 + *command.len - 1 + strlen(current_dir_name(getcwd(NULL, 250))) + 3);

					else if (prompt_type == "1")
						mvdelch(*line, sizeof(USERNAME) + *command.len + 3);

					else if (prompt_type == "2")
						mvdelch(*line, *command.len + 1);


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

	/*
	 * turns the attribute off and end the window
	 */

	attroff(COLOR_PAIR(using_color_index));
	endwin();

	return 0;
}
