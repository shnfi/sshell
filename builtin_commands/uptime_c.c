#include <stdio.h>

void uptime_c(long ut, int *al)
{
   int hour = ut / 3600;
   int min = (ut % 3600) / 60;

   printw("\n\n");
   printw("Started about %02d:%02d hour", hour, min);

   *al += 1;
}