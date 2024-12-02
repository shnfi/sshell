char *trim_extra_spaces(char str[])
{
   char *trimed_str = malloc(30);

   memset(trimed_str, 0, sizeof(trimed_str));

   for (int i = 0; i < strlen(str); i++)
   {
      if (str[i] == ' ' && str[i + 1] != '-')
      {
         continue;
      }
      else
      {
         trimed_str[strlen(trimed_str)] = str[i];
      }
   }

   return trimed_str;
}