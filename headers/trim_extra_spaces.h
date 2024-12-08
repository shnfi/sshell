#include <string.h>

char *trim_extra_spaces(char str[])
{
   int founded_chars;

   /*
    * removing spaces of the beggining 
    */

   for (int i = 0; i < strlen(str); i++)
   {
      if (str[i] == ' ')
      {
         memmove(&str[i], &str[i + 1], strlen(str) - i);
      }
      else break;
   }

   /*
    * removing spaces of the end 
    */

   for (int i = strlen(str) - 1; i > 0; i--)
   {
      if (str[i] == ' ')
      {
         memmove(&str[i], &str[i + 1], strlen(str) - i);
      }
      else break;
   }

   return str;
}