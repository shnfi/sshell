#include <string.h>

#ifndef BUFFER
   #define BUFFER 30
#endif

char *current_dir_name(char cwd[])
{
   static char dir_n[BUFFER];
   static char r_dir_n[BUFFER];

   memset(dir_n, 0, sizeof(dir_n));
   memset(r_dir_n, 0, sizeof(r_dir_n));

   for (int i = strlen(cwd) - 1; i >= 0; i--)
   {
      if (cwd[i] != '/')
      {
         dir_n[strlen(dir_n)] = cwd[i];
      }
      else break;
   }

   for (int i = strlen(dir_n) - 1; i >= 0; i--) r_dir_n[strlen(r_dir_n)] = dir_n[i];

   return r_dir_n;
}