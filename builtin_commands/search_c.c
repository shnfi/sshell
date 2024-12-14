#include <stdlib.h>

void search_c(char str[], int *line, int *command_len)
{
   char *command = malloc(207);
   char *val = malloc(200);

   for (int i = 7; i < strlen(str); i++)
   {
      if (str[i] != ' ')
      {
         val[strlen(val)] = str[i];
      }
      else 
      {
         val[strlen(val)] = '+';
      }
   }

   sprintf(command, "firefox 'https://www.google.com/search?client=ubuntu-sn&channel=fs&q=%s' -safe-mode", val);

   system(command);

   clear_c(line, str, command_len);

   free(command);
   free(val);
}