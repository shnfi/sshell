#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void echo_c(char str[], int *al)
{
   printw("\n\n");

   if (strstr(str, "$") != NULL)
   {
      /*
       * echoing the local variable of the system
       */
      
      char *x = malloc(12);

      memset(x, 0, sizeof(x));

      for (int i = 6; i < strlen(str) && str[i] != ' '; i++)
      {
         x[strlen(x)] = str[i];
      }

      printf("%s\n", x);

      char *l_var = getenv(x);

      if (l_var != NULL)
      {
         printw("%s", l_var);
      }
      else
      {
         printw(" * This local variable not existed!");
      }

      free(x);

      *al += 1;
   }
   else
   {
      /*
       * echoing the given value
       */
      
      for (int i = 5; i < strlen(str); i++)
      {
         printw("%c", str[i]);
      }
      
      *al += 1;
   }
}