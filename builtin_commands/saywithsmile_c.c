#include <stdio.h>
#include <string.h>

void saywithsmile_c(char str[], int *al)
{
   unsigned int index_of_whitespace;

   for (int i = 0; i <= strlen(str); i++)
   {
      if (str[i] == ' ') 
      {
         index_of_whitespace = i;
         break;
      }
   }

   printw("\n\n");

   for (int i = 0; i < (strlen(str) - index_of_whitespace) + 1; i++)
      printw("-");

   printw("\n");

   for (int i = index_of_whitespace; i < strlen(str); i++)
      printw("%c", str[i]);

   printw("\n");
   
   for (int i = 0; i < (strlen(str) - index_of_whitespace) + 1; i++)
      printw("-");
   
   printw("\n");

   for (int i = 0; i < (strlen(str) - index_of_whitespace) / 3; i++)
   {
      printw(" ");

      if (i == (strlen(str) - index_of_whitespace) / 3 - 1) printw("¯\\_(*o*)_/¯");
   }

   *al += 4;
}