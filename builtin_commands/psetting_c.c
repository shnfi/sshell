#include <stdio.h>
#include <string.h>

#include "headers/check_for_arg.h"

void psetting_c(char str[], char **c_or_d, char **r_or_s, char **prompt_type)
{  
   if (check_for_arg(str, "c") == 1)
   {
      *c_or_d = "clock";
      *prompt_type = "-1";
   }
   
   if (check_for_arg(str, "d") == 1)
   {
      *c_or_d = "date";
      *prompt_type = "-1";
   }
   
   if (check_for_arg(str, "r") == 1)
   {
      *r_or_s = "round";
      *prompt_type = "-1";
   }
   
   if (check_for_arg(str, "s") == 1)
   {
      *r_or_s = "square";
      *prompt_type = "-1";
   }

   if (check_for_arg(str, "1") == 1)
   {
      *c_or_d = "-1";
      *r_or_s = "-1";
      *prompt_type = "1";
   }

   if (check_for_arg(str, "2") == 1)
   {
      *c_or_d = "-1";
      *r_or_s = "-1";
      *prompt_type = "2";
   }
}