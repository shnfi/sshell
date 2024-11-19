#include <stdio.h>
#include <string.h>

void psetting_c(char str[], char **c_or_d)
{
   /*
    * argument parsing
    */
   
   char *arg = malloc(3);
   int index_of_dash;

   for (int i = 0; i < strlen(str); i++)
   {
      if ((str[i] == '-') == 1) index_of_dash = i;

      if (i >= index_of_dash && i > 8)
      {
         arg[strlen(arg)] = str[i];
      }
      else continue;
   }

   /*
    * making the final decision 
    */
   
   if (strcmp(arg, "-c") == 0)
   {
      *c_or_d = "c";
   }
   else if (strcmp(arg, "-d") == 0)
   {
      *c_or_d = "d";
   }
}