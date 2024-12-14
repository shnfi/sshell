#include <stdio.h>
#include <string.h>

void cd_c(char str[])
{
   unsigned int ws_index;
   char *new_dir = malloc(30);
   char *re_new_dir = malloc(30);

   memset(new_dir, 0, sizeof(new_dir));
   memset(re_new_dir, 0, sizeof(re_new_dir));

   int x = 0;

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

   chdir(re_new_dir);

   free(new_dir);
}