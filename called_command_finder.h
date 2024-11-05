# include <string.h>

char *called_command_finder(char str[])
{
   static char output[15];

   memset(output, 0, sizeof(output));

   for (int i = 0; i < strlen(str); i++)
   {
      if (str[i] != ' ') output[strlen(output)] = str[i];
      else break;
   }

   return output;
}