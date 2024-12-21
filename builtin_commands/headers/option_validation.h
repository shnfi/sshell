char *option_validation(char str[], char *valid_options[], int valid_options_size)
{
   char *args_string = malloc(8);

   memset(args_string, 0, sizeof(args_string));

   int occupied_lines;
   int index_of_dashes[5];
   int x = 0;

   for (int i = 0; i < strlen(str); i++)
   {
      if (str[i] == '-')
      {
         index_of_dashes[x] = i;
         x++;
      }
      else continue;
   }

   for (int i = 0; i < x; i++)
   {
      for (int j = index_of_dashes[i]; j < strlen(str); j++)
      {
         if (str[j] != ' ')
         {
            args_string[strlen(args_string)] = str[j];
         }
      }
   }

   /*
    * checking for invalid options
    */

   if (x > 0)
   {
      bool er = false;

      for (int i = 1; i < strlen(args_string); i++)
      {
         for (int j = 0; j < valid_options_size; j++)
         {
            char *ASI_PTR = malloc(10);

            sprintf(ASI_PTR, "%c", args_string[i]);

            if (strcmp(ASI_PTR, valid_options[j]) == 0)
            {
               er = false;
               free(ASI_PTR);
               break;
            }
            else
            {
               er = true;
               free(ASI_PTR);
            }
         }

         if (er)
         {
            char *ASI_PTR = malloc(10);
            sprintf(ASI_PTR, "%c", args_string[i]);
            return ASI_PTR;

            free(ASI_PTR);
         }
         else if (!er && i == strlen(args_string) - 1)
            return "okay";
      }
   }
   else
      return "okay";
}