#include <stdio.h>
#include <dirent.h>

int check_for_arg(char str[], char arg[]);

void ls_c(char str[], char cwd[], int *al)
{
   DIR *path = opendir(cwd);
   struct dirent *d = readdir(path);

   int occupied_lines;

   printw("\n\n");

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
         // free(file);

         return;
      }
   }
}