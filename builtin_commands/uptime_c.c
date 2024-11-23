#include <stdio.h>

void uptime_c(long ut, int *al)
{
   int hour = ut / 3600;
   int min = (ut % 3600) / 60;

   printw("\n\n");
   printw("%d:%d", hour, min);

   *al += 1;
}