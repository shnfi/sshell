#include <stdio.h>
#include <dirent.h>

void ls_c(char cwd[], int *al, char mode)
{
   DIR *path = opendir(cwd);
   struct dirent *d = readdir(path);

   int occupied_lines;

   printw("\n\n");

   while (d != NULL)
   {
      char symbol;

      /*
       * checking the type of the file in the directory and setting the symbol for listing it
       */

      if (d->d_type == DT_DIR) symbol = 'D';
      else if (d->d_type == DT_REG) symbol = 'F';
      else if (d->d_type == DT_UNKNOWN) symbol = '?';
      else symbol = 'X';

      /*
       * preparing the size of each file 
       */

      FILE *file = fopen(d->d_name, "r");
      long file_size;

      if (file != NULL) {
         fseek(file, 0, SEEK_END);
         file_size = ftell(file);

         /*
          * for directories, '.' (current directory) and '..' (parent directory) it shows
          * the 9223372036854775807 number as the size, this line will handle this bug and shows the real size of them
          */

         if (file_size == 9223372036854775807) file_size = 4096;

         fclose(file);
         file = NULL;
         free(file);
      }
      else break;

      /*
       * listing the directories 
       */

      if (mode == 'n')
      {
         if (d->d_name[0] != '.')
         {
            printw("[ %c ]  [ %10ld B ]  %s\n", symbol, file_size, d->d_name);
            *al += 1;
         }
      }
      else if (mode == 'a')
      {
         printw("[ %c ]  [ %10ld B ]  %s\n", symbol, file_size, d->d_name);
         *al += 1;
      }

      d = readdir(path);

      if ((char *) d == NULL) 
      {
         free(path);
         free(d);
         free(file);

         return;
      }
   }
}