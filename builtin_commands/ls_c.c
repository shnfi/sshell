#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

#include "headers/option_validation.h"

int check_for_arg(char str[], char arg[]);

void ls_c(char str[], char cwd[], int *al)
{
   DIR *path = opendir(cwd);
   struct dirent *d = readdir(path);

   char *valid_options[5] = { "l", "t", "r", "h", "a" };

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

   while (d != NULL)
   {
      char symbol;

      /*
       * checking the type of the file in the directory and setting the symbol for listing it
       */

      if (d->d_type == DT_DIR) symbol = 'D';
      else if (d->d_type == DT_REG) symbol = 'F';
      else if (d->d_type == DT_UNKNOWN) symbol = '?';
      else symbol = 'X';

      /*
       * preparing the size of each file 
       */

      if (d->d_name[0] != '.')
      {
         printw("[ %c ] %s\n", symbol, d->d_name);
         *al += 1;
      }

      d = readdir(path);

      if ((char *) d == NULL) 
      {
         free(path);
         free(d);

         return;
      }
   }
}