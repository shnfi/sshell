#include <stdio.h>

void pwd_c(char cwd[], int *al)
{
   printw("\n\n");
   printw("%s", cwd);

   *al += 1;
}