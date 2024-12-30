void command_identification(
   char command_data[], char USERNAME[], int *additional_line, bool *EXIT, int *line, int *command_len, char *clock_or_date[], char *round_or_square[], int MAIN_LINE_BUFFER, struct sysinfo info,
   char *prompt_type[], int *using_color_index
   )
{
   if (strcmp(called_command_finder(trim_extra_spaces(command_data)), "help") == 0) help_c(command_data, USERNAME, additional_line);
   else if (strcmp(trim_extra_spaces(command_data), "exit") == 0) exit_c(EXIT);
   else if (strcmp(trim_extra_spaces(command_data), "clear") == 0) clear_c(line, command_data, command_len);
   else if (strcmp(trim_extra_spaces(command_data), "cd") == 0) { chdir("/home/"); chdir(USERNAME); } /* navigating to the home directory shortcut */
   else if (strcmp(called_command_finder(trim_extra_spaces(command_data)), "saywithsmile") == 0) saywithsmile_c(command_data, additional_line);
   else if (strcmp(called_command_finder(trim_extra_spaces(command_data)), "cd") == 0) cd_c(command_data);
   else if (strcmp(called_command_finder(trim_extra_spaces(command_data)), "ls") == 0) ls_c(command_data, getcwd(NULL, 100), additional_line);
   else if (strcmp(called_command_finder(trim_extra_spaces(command_data)), "psetting") == 0) psetting_c(command_data, clock_or_date, round_or_square, prompt_type, additional_line, using_color_index);
   else if (strcmp(trim_extra_spaces(command_data), "pwd") == 0) pwd_c(getcwd(NULL, 100), additional_line);
   else if (strcmp(trim_extra_spaces(command_data), "uptime") == 0) uptime_c(info.uptime, additional_line);
   else if (strcmp(called_command_finder(trim_extra_spaces(command_data)), "touch") == 0) touch_c(getcwd(NULL, 100), command_data);
   else if (strcmp(called_command_finder(trim_extra_spaces(command_data)), "mkdir") == 0) mkdir_c(getcwd(NULL, 100), command_data);
   else if (strcmp(called_command_finder(trim_extra_spaces(command_data)), "rm") == 0) rm_c(getcwd(NULL, 100), command_data);
   else if (strcmp(called_command_finder(trim_extra_spaces(command_data)), "echo") == 0) echo_c(command_data, additional_line);
   else if (strcmp(called_command_finder(trim_extra_spaces(command_data)), "search") == 0) search_c(command_data, line, command_len);
   else if (strcmp(called_command_finder(trim_extra_spaces(command_data)), "sizeof") == 0) sizeof_c(command_data, additional_line);
   else
   {
      /*
       * running the entered command if it was not one of the specific 
       * commands that we checked in the last few lines 
       */

      char *returning_output = malloc(MAIN_LINE_BUFFER);
      FILE *output;
   
      output = popen(command_data, "r");

      if (output == NULL)
      {
         attron(COLOR_PAIR(3));

         printw(" [ERROR] Error while opening the pipe.");
         *al += 1;

         attroff(COLOR_PAIR(3));

         return "ERROR";
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
}