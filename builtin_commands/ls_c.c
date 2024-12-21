#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

int check_for_arg(char str[], char arg[]);

void ls_c(char str[], char cwd[], int *al)
{
   DIR *path = opendir(cwd);
   struct dirent *d = readdir(path);

   char *valid_options[5] = { "l", "t", "r", "h", "a" };
   char *args_string = malloc(8);

   memset(args_string, 0, sizeof(args_string));

   int occupied_lines;
   int index_of_dashes[5];
   int x = 0;

   printw("\n\n");

   for (int i = 0; i < strlen(str); i++)
   {
      if (str[i] == '-')
      {
         index_of_dashes[x] = i;
         x++;
      }
      else continue;
   }

   for (int i = 0; i < x; i++)
   {
      for (int j = index_of_dashes[i]; j < strlen(str); j++)
      {
         if (str[j] != ' ')
         {
            args_string[strlen(args_string)] = str[j];
         }
      }
   }

   /*
    * checking for invalid options
    */

   bool er = false;

   for (int i = 1; i < strlen(args_string); i++)
   {
      for (int j = 0; j < sizeof(valid_options) / sizeof(valid_options[0]); j++)
      {
         char *ASI_PTR = malloc(10);

         sprintf(ASI_PTR, "%c", args_string[i]);

         if (strcmp(ASI_PTR, valid_options[j]) == 0)
         {
            er = false;
            break;
         }
         else
            er = true;
      }

      if (er)
      {
         printw(" * Invalid options used: %c\n", args_string[i]);
         *al += 1;
         return;
      }
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