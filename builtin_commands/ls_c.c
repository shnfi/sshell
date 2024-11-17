#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

void ls_c(char cwd[], int *al)
{
   DIR *path = opendir(cwd);
   struct dirent *d = readdir(path);

   int occupied_lines;

   printw("\n\n");

   while (d != NULL)
   {
      struct stat stats;
      char symbol;

      /*
       * checking the type of the file in the directory and setting the symbol for listing it
       */

      if (stat(d->d_name, &stats) == 0)
      {
         if (S_ISDIR(stats.st_mode)) symbol = 'D';
         else symbol = 'F';
      }
      else break;

      /*
       * listing the directories 
       */

      printw("[%c] %s\n", symbol, d->d_name);
      d = readdir(path);

      occupied_lines++;
   }

   *al += occupied_lines;
}