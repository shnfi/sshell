#include <stdio.h>
#include <string.h>

void cd_c(char str[], int *al, int *using_color_index)
{
   unsigned int ws_index;
   char *new_dir = malloc(30);
   char *re_new_dir = malloc(30);

   memset(new_dir, 0, sizeof(new_dir));
   memset(re_new_dir, 0, sizeof(re_new_dir));

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

      free(new_dir);

      return;
   }

   free(new_dir);
}