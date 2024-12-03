#include <string.h>

int check_for_arg(char str[], char arg[])
{
   char *args_string = malloc(8);

   memset(args_string, 0, sizeof(args_string));

   int index_of_dashes[5];
   int x = 0;

   for (int i = 0; i < strlen(str); i++)
   {
      if (str[i] == '-')
      {
         index_of_dashes[x] = i;
         x++;
      }
      else continue;
   }

   for (int i = 0; i < x; i++)
   {
      for (int j = index_of_dashes[i]; j < strlen(str); j++)
      {
         if (str[j] != ' ')
         {
            args_string[strlen(args_string)] = str[j];
         }
      }
   }

   memmove(&args_string[0], &args_string[1], strlen(args_string) + 1);

   return 1 ? strstr(args_string, arg) != NULL : 0;
}