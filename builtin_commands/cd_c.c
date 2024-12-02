#include <stdio.h>
#include <string.h>

void cd_c(char str[])
{
   unsigned int ws_index;
   char *new_dir = malloc(30);

   memset(new_dir, 0, sizeof(new_dir));

   for (int i = 0; i < strlen(str); i++)
   {
      if (str[i] == ' ')
      {
         ws_index = i+1;
         break;
      }
   }

   for (int i = ws_index; i < strlen(str); i++) new_dir[strlen(new_dir)] = str[i];

   chdir(new_dir);
}