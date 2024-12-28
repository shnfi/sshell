#include <stdio.h>
#include <string.h>

#include "headers/check_for_arg.h"

char *option_validation(char str[], char *valid_options[], int valid_options_size);

void psetting_c(char str[], char **c_or_d, char **r_or_s, char **prompt_type, int *al, int *using_color_index)
{
   char *valid_options[12] = { "c", "d", "r", "s", "1", "2", "w", "g", "t", "b", "m", "y" };

   char *validate_output = option_validation(str, valid_options, sizeof(valid_options) / sizeof(valid_options[0]));

   printw("\n\n");

   if (strcmp(validate_output, "okay") != 0)
   {
		attron(COLOR_PAIR(3));

      printw(" [ERROR] Invalid options used: %s\n", validate_output);
      *al += 1;

		attroff(COLOR_PAIR(3));

      return;
   }

   if (check_for_arg(str, "c") == 1)
   {
      *c_or_d = "clock";
      *prompt_type = "-1";
   }
   
   if (check_for_arg(str, "d") == 1)
   {
      *c_or_d = "date";
      *prompt_type = "-1";
   }
   
   if (check_for_arg(str, "r") == 1)
   {
      *r_or_s = "round";
      *prompt_type = "-1";
   }
   
   if (check_for_arg(str, "s") == 1)
   {
      *r_or_s = "square";
      *prompt_type = "-1";
   }

   if (check_for_arg(str, "1") == 1)
   {
      *c_or_d = "-1";
      *r_or_s = "-1";
      *prompt_type = "1";
   }

   if (check_for_arg(str, "2") == 1)
   {
      *c_or_d = "-1";
      *r_or_s = "-1";
      *prompt_type = "2";
   }

   if (check_for_arg(str, "w") == 1)
   {
      attron(COLOR_PAIR(1));
      *using_color_index = 1;
   }

   if (check_for_arg(str, "g") == 1)
   {
      attron(COLOR_PAIR(2));
      *using_color_index = 1;
   }

   if (check_for_arg(str, "t") == 1)
   {
      attron(COLOR_PAIR(3));
      *using_color_index = 2;
   }

   if (check_for_arg(str, "b") == 1)
   {
      attron(COLOR_PAIR(4));
      *using_color_index = 3;
   }

   if (check_for_arg(str, "m") == 1)
   {
      attron(COLOR_PAIR(5));
      *using_color_index = 4;
   }

   if (check_for_arg(str, "y") == 1)
   {
      attron(COLOR_PAIR(6));
      *using_color_index = 5;
   }
}