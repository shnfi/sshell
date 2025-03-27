void sizeof_c(char str[], int *al, int *using_color_index)
{
   char *arg = malloc(50);
   char *re_arg = malloc(50);
   char *f_name = malloc(50);

   memset(arg, 0, 50);
   memset(re_arg, 0, 50);
   memset(f_name, 0, 50);

   printw("\n\n");

   int x = 0;

   for (int i = strlen(str) - 1; i > 0; i--)
   {
      if (str[i] != ' ')
      {
         arg[x] = str[i];
         x++;
      }
      else break;
   }
   
   for (int i = strlen(arg); i >= 0; i--)
      re_arg[strlen(re_arg)] = arg[i];

   FILE *f = fopen(re_arg, "r");
   long f_size;

   if (f != NULL)
   {
      fseek(f, 0, SEEK_END);
      f_size = ftell(f);
      fclose(f);
   }
   else
   {
      attron(COLOR_PAIR(3));

      printw(" [ERROR] The file does not existed.");
      *al += 1;

      attroff(COLOR_PAIR(3));
      attron(COLOR_PAIR(*using_color_index));

      return;
   }

   if (f_size == 9223372036854775807)
      f_size = 4096;

   printw("%ld bytes", f_size);

   *al += 1;

   free(arg);
   free(re_arg);
   free(f_name);
}
