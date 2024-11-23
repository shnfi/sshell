#include <stdio.h>

void uptime_c(long ut, int SS, int SM, int SH, int *al)
{
   int hour = ut / 3600;
   int min = (ut % 3600) / 60;

   printw("\n\n");
   printw("Started from %02d:%02d:%02d - Started about %02d:%02d hour", SS, SM, SH, hour, min);

   *al += 1;
}