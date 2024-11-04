# include <stdio.h>
# include <string.h>

# define BUFF 100

void saywithsmile_c(char str[], int *al)
{
   int index_of_whitespace;

   for (int i = 0; i < strlen(str); i++)
   {
      if (str[i] == ' ') 
      {
         index_of_whitespace = i;
         break;
      }
   }

   printw("\n\n:) -> ");
   for (int i = index_of_whitespace; i < strlen(str); i++) printw("%c", str[i]); 

   *al += 1;
}