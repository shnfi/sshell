#include <stdio.h>
#include <string.h>

void cd_c(char str[], int *al, int *using_color_index)
{
   unsigned int ws_index;
   char *new_dir = malloc(50);
   char *re_new_dir = malloc(50);

   memset(new_dir, 0, 50);
   memset(re_new_dir, 0, 50);

   int x = 0;

   printw("\n\n");

   for (int i = strlen(str) - 1; i > 0; i--)
   {
      if (str[i] != ' ')
      {
         new_dir[(strlen(str) - 1) - ((strlen(str) - 1) - x)] = str[i];
         x++;
      }
      else break;
   }

   for (int i = strlen(new_dir); i >= 0; i--)
      re_new_dir[strlen(re_new_dir)] = new_dir[i];

   if (chdir(re_new_dir) == -1)
   {
      attron(COLOR_PAIR(3));

      printw(" [ERROR] This directory does not existed!");
      *al += 1;

      attroff(COLOR_PAIR(3));
      attron(COLOR_PAIR(*using_color_index));

      new_dir = NULL;
      re_new_dir = NULL;

      free(new_dir);
      free(re_new_dir)

      return;
   }

   new_dir = NULL;
   re_new_dir = NULL;

   free(new_dir);
   free(re_new_dir)
}
