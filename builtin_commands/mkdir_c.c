#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

void mkdir_c(char cwd[], char str[])
{
   bool ws_founded = false;
   char *arg = malloc(20);
   char *re_arg = malloc(20);
   char *file_path = malloc(100);

   memset(arg, 0, sizeof(arg));
   memset(re_arg, 0, sizeof(re_arg));

   file_path = cwd;

   file_path[strlen(file_path)] = '/';

   int x = 0;

   for (int i = strlen(str) - 1; i > 0; i--)
   {
      if (str[i] != ' ')
      {
         arg[(strlen(str) - 1) - ((strlen(str) - 1) - x)] = str[i];
         x++;
      }
      else break;
   }

   for (int i = strlen(arg); i >= 0; i--)
      re_arg[strlen(re_arg)] = arg[i];

   printw("\n%s", arg);
   printw("\n%s", re_arg);

   strcat(file_path, re_arg);

   mkdir(file_path, 0755);

   free(arg);
   free(re_arg);
   free(file_path);
}