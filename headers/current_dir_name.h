#include <string.h>

#define CDN_BUFFER 25

char *current_dir_name(char cwd[])
{
   char *dir_n = malloc(CDN_BUFFER);
   int index_of_s;

   memset(dir_n, 0, sizeof(dir_n));

   for (int i = strlen(cwd); i >= 0; i--)
   {
      if (cwd[i] == '/')
      {
         index_of_s = i;
         break;
      }
   }

   for (int i = 0; i < (strlen(cwd) - index_of_s - 1); i++)
   {
      dir_n[strlen(dir_n)] = cwd[(index_of_s + 1) + i];
   }

   return dir_n;

   free(dir_n);
}