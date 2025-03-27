#include <stdio.h>
#include <string.h>

void rm_c(char cwd[], char str[], int *al, int *using_color_index)
{
   bool ws_founded = false;
   char *arg = malloc(50);
   char *re_arg = malloc(50);
   char *file_path = malloc(1024);

   memset(arg, 0, 50);
   memset(re_arg, 0, 50);
   memset(file_path, 0, 1024);

   strcpy(file_path, cwd);

   file_path[strlen(file_path)] = '/';

   int x = 0;

   printw("\n\n");

   for (int i = strlen(str) - 1; i > 0; i--)
   {
      if (str[i] != ' ')
      {
         arg[x] = str[i];
         x++;
      }
      else break;
   }

   for (int i = strlen(arg); i >= 0; i--)
      re_arg[strlen(re_arg)] = arg[i];

   strcat(file_path, re_arg);

   if (remove(file_path) == -1)
   {
      if (rmdir(file_path) == -1)
      {
         attron(COLOR_PAIR(3));

         printw(" [ERROR] This file/directory does not existed!");
         *al += 1;

         attroff(COLOR_PAIR(3));
         attron(COLOR_PAIR(*using_color_index));

         arg = NULL;
         re_arg = NULL;
         file_path = NULL;

         free(arg);
         free(re_arg);
         free(file_path);

         return;
      }
   }
}
