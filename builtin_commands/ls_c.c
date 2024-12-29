#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

#include "headers/option_validation.h"

int check_for_arg(char str[], char arg[]);

void ls_c(char str[], char cwd[], int *al)
{
   char *valid_options[5] = { "l", "t", "r", "h", "a" };

   char *validate_output = option_validation(str, valid_options, sizeof(valid_options) / sizeof(valid_options[0]));

   int index_of_dashes[5];
   int x = 0;

   char *dir_name = malloc(50);

   memset(dir_name, 0, sizeof(dir_name));

   /*
    * the 'last_option_index' is setted to the 2 because the first whitespace is between
    * the 'ls' and the '-' 
    */

   int last_option_index = 2;

   printw("\n\n");

   if (strcmp(validate_output, "okay") != 0)
   {
		attron(COLOR_PAIR(3));

      printw(" [ERROR] Invalid options used: %s\n", validate_output);
      *al += 1;

		attroff(COLOR_PAIR(3));

      return;
   }

   /*
    * this two 'for' loops are for getting the index of the white space that end to the options
    */

   for (int i = 0; i < strlen(str); i++)
   {
      if (str[i] == '-')
      {
         index_of_dashes[x] = i;
         x++;
      }
      else
         continue;
   }

   if (x > 0)
   {
      for (int i = index_of_dashes[(sizeof(index_of_dashes) / sizeof(index_of_dashes[0])) - 1]; i < strlen(str); i++)
      {
         if (str[i] == ' ')
         {
            if (last_option_index != i)
            {
               last_option_index = i;
               break;
            }
         }
      }
   }

   /*
    * now trying to get the directory name
    */

   for (int i = last_option_index + 1; i < strlen(str); i++)
      dir_name[strlen(dir_name)] = str[i];

   /*
    * at the end the main directory listing task..
    */

   DIR *path;

   if (strlen(dir_name) == 0)
      path = opendir(cwd);
   else
   {
      path = opendir(dir_name);

      if (path == NULL)
      {
         attron(COLOR_PAIR(3));

         printw(" [ERROR] This directory does not existed!");
         *al += 1;

         attroff(COLOR_PAIR(3));

         return;
      }
   }

   struct dirent *d = readdir(path);

   while (d != NULL)
   {
      char symbol;

      /*
       * checking the type of the file in the directory and setting the symbol for listing it
       */

      if (d->d_type == DT_DIR)
         symbol = 'D';
      else if (d->d_type == DT_REG)
         symbol = 'F';
      else if (d->d_type == DT_UNKNOWN)
         symbol = '?';
      else
         symbol = 'X';

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
         free(dir_name);

         return;
      }
   }
}