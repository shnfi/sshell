#include <stdio.h>
#include <dirent.h>

void ls_c(char cwd[], int *al)
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
       * listing the directories 
       */

      printw("[ %c ] %s\n", symbol, d->d_name);
      d = readdir(path);

      occupied_lines++;
   }

   *al += occupied_lines;
}