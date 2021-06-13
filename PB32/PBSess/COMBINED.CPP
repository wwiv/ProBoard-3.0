#include "proboard.hpp"
#include <string.h>
#include <stdlib.h>

void
mCombinedSelect(char *data)
{
  int count = 0;
  TpMsgArea ma;
   bool mailcheck = FALSE;

   if(QString(data) == QString("/M")) mailcheck = TRUE;

   for(;;)
   {
      io << "\f\n\7";

      if(mailcheck)
      {
         io << S_SELECT_AREAS_TO_SCAN_TITLE << "\n\n";
      }
      else
      {
         io << S_SELECT_COMBINED_AREAS_TITLE << "\n\n";
      }

      LineCounter(4);
      EnableStop();

      for(int i=1,count=0;i<=TpMsgArea::highAreaNum() && i<=1000;i++)
      {
         QString checked = ' ';

         if(!ma.read(i))
            continue;

         if(!user.CheckAccess(ma.readLevel,ma.readFlags,ma.readFlagsNot) && !ma.sysopAccess())
            continue;

         if(mailcheck)
         {
            if(user.mailCheckBoards.connected(i))
               checked = 'û';
         }
         else
         {
            if(user.combinedBoards.connected(i))
               checked = 'û';
         }

         io << form(" \3%3d. \2%s \6%-30.30s ",i,(char *)checked,ma.name);

         if(OutputStopped) break;

         if(!((++count)%2))
         {
            io << '\n';
            if(LineCounter()) break;
         }
      }

      if(count%2) io << '\n';

      io << '\n' << S_SELECT_AREAS_TO_TOGGLE;

      char s[41];

      Input(s,40);

      if(!s[0]) break;

      char *ptr = strtok(s," ,");

      while(ptr)
      {
         int area = atoi(ptr);
         if(area>=1 && area<=1000)
         {
            if(mailcheck)
            {
               user.mailCheckBoards.toggle(area);
               LOG(3,"Area #%d toggled for mailcheck",area);
            }
            else
            {
               user.combinedBoards.toggle(area);
               LOG(3,"Combined area #%d toggled",area);
            }
         }

         ptr = strtok(NULL," ,");
      }
   }
}

void
mCombinedClear(char *data)
{
   int i;
   bool mailcheck = FALSE;

   if(QString(data) == QString("/M")) mailcheck = TRUE;

   io << '\n' << S_ENABLE_OR_DISABLE_ALL_AREAS;

   switch(WaitLanguageHotkeys(K_ENABLE_OR_DISABLE_ALL_AREAS))
   {
      case 1:
         {
            for(i=1;i<=1000;i++)
            {
               if(mailcheck)
                  user.mailCheckBoards.disconnect(i);
               else
                  user.combinedBoards.disconnect(i);
            }

            io << S_ALL_AREAS_DISABLED << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
         }
         break;
      case 0:
         {
            for(i=1;i<=1000;i++)
            {
               if(mailcheck)
                  user.mailCheckBoards.connect(i);
               else
                  user.combinedBoards.connect(i);
            }

            io << S_ALL_AREAS_ENABLED << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
         }
         break;
   }
}

