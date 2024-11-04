# include <stdio.h>
# include <string.h>

void saywithsmile_c(char str[], int *al)
{
   int ws = 0;
   char *output = malloc(100);

   for (int i = 0; i < strlen(str); i++)
   {
      if (str[i] == ' ') ws++;

      if (ws >= 1) output[strlen(output)] = str[i];
   }

   printw("\n\n:) -> %s\n", output);

   free(output);

   *al += 1;
}