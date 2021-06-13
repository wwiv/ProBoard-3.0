#include "proboard.hpp"

#include <string.h>

void
mShowBulletin(char *data)
{
   char fname[9];

   int i;
   for(i=0;data[i]==' ';i++) {}

   char *s = &data[i];
   for(;data[i] && data[i]!=' ';i++) {}
   data[i] = '\0';

   QString prompt;

   for(i++;data[i]==' ';i++) {}

   if(data[i])
      prompt = &data[i];
   else
      prompt = S_ENTER_BULLETIN;

   for(;;)
   {
      strcpy(fname,s);

      io << '\n';

      ShowAnsiFile(fname);

      io << "\n\7" << prompt;

      Input(&fname[strlen(fname)],8-strlen(fname),INPUT_UPALL);

      if(strlen(fname) <= strlen(s)) break;

      if(ShowAnsiFile(fname,NULL) == SENDFILE_NOTFOUND)
         io << "\n\n" << S_FILE_NOT_FOUND << ' ' << S_PRESS_ENTER_TO_CONTINUE;
      else
         io << '\n' << S_PRESS_ENTER_TO_CONTINUE;
   }
}

