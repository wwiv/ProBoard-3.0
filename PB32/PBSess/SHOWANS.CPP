#include "proboard.hpp"

int
mShowAnsiFile(char *data)
{
   return ShowAnsiFile(data,NULL);
}

int
mShowAnsiFileAndWait(char *data)
{
   int r = ShowAnsiFile(data,NULL);

   io << '\n' << S_PRESS_ENTER_TO_CONTINUE;

   return r;
}


char
ShowAnsiFile(char *data,char *hotkeys)
{
   QFileName f(cfg.txtPath,data);
   char k;

   if(Terminal() == Avatar)
   {
      f.changeExt("AVT");
      k = SendFile(f,hotkeys);
      if(k != SENDFILE_NOTFOUND) return k;
   }

   if(Terminal() == Ansi)
   {
      f.changeExt("ANS");
      k = SendFile(f,hotkeys);
      if(k != SENDFILE_NOTFOUND) return k;
   }

   Color(7);

   f.changeExt("ASC");
   k = SendFile(f,hotkeys);

   return k;
}

