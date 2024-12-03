#include <stdio.h>
#include <string.h>

#include "headers/check_for_arg.h"

void psetting_c(char str[], char **c_or_d, char **r_or_s)
{  
   if (check_for_arg(str, "c") == 1)
   {
      *c_or_d = "clock";
   }
   
   if (check_for_arg(str, "d") == 1)
   {
      *c_or_d = "date";
   }
   
   if (check_for_arg(str, "r") == 1)
   {
      *r_or_s = "round";
   }
   
   if (check_for_arg(str, "s") == 1)
   {
      *r_or_s = "square";
   }
}