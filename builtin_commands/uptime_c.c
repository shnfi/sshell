#include <stdio.h>

void uptime_c(long ut, int *al)
{
   int hour = ut / 3600;
   int min = (ut % 3600) / 60;

   printw("\n\n");
   
   if (hour == 0)
   {
      printw("Started about %02d minutes", min);
   }
   else
   {
      printw("Started about %02d:%02d hours", hour, min);
   }

   *al += 1;
}