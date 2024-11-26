#include <stdio.h>
#include <string.h>

void rm_c(char cwd[], char str[])
{
   bool ws_founded = false;
   char *arg = malloc(20);
   char *file_path = malloc(100);

   file_path = cwd;

   file_path[strlen(file_path)] = '/';

   for (int i = 0; i < strlen(str); i++)
   {
      if (str[i - 1] == ' ') ws_founded = true;

      if (ws_founded) arg[strlen(arg)] = str[i];
   }

   strcat(file_path, arg);

   remove(file_path);

   free(arg);
   free(file_path);
}