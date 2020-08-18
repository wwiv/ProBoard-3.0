#include "proboard.hpp"

#include <time.h>

#define VERSION "3.00à"

void
ShowIntro()
{
   io << "ProBoard v" VERSION << " (c) 1990-1996  Philippe Leybaert\n\n";

   if(BaudRate)
      Delay(2000);

   QString response;

   long tm = time(NULL);

   while((time(NULL)-tm) < 2 && BaudRate)
   {
      char k = ReadKey();

      if(!k)
         continue;

      response << k;

      if(strstr( response , "\x1b["))
      {
         user.uFlags |= UFLAG_ANSI;
         break;
      }
   }

   if(!BaudRate)
      user.uFlags |= UFLAG_ANSI;

   while(ReadKey());

   if(SendFile(form("INTRO%d.ANS",1/*node_number*/)) == SENDFILE_NOTFOUND)
      if(SendFile("INTRO.ANS") == SENDFILE_NOTFOUND)
         SendFile("LOGO.ANS");
}
