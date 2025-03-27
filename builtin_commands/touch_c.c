#include <string.h>

void touch_c(char cwd[], char str[], int *al, int *using_color_index)
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

   FILE *f_creation;
   FILE *f_check_for_existence = fopen(file_path, "r");

   if (f_check_for_existence != 0)
   {
      attron(COLOR_PAIR(3));

      printw(" [ERROR] Cannot create this file!");
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
   else 
      f_creation = fopen(file_path, "w");
}
