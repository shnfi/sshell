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
      if (d->d_name != "." || d->d_name != "..")
      {
         // printw("(^) %s\n", d->d_name);
         // printw("[_] %s\n", d->d_name);
         printw("(_) %s\n", d->d_name);
         d = readdir(path);
         occupied_lines++;
      }
      else continue;
   }

   *al += occupied_lines;
}