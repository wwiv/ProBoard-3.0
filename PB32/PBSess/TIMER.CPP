#include "proboard.hpp"

#include <stdio.h>
#include <time.h>
#include <string.h>


void
UpdateStatusBar()
{

}

/*
void
update_display()
{
   static int oldmode = 0;

   update_user_window();

   if(user_recnr>=0)
   {
    char s[100];
    if(oldmode!=display_mode)
      {
      tsw_clearrect(1,tsw_vsize,tsw_hsize,tsw_vsize,0x70);
      oldmode=display_mode;
      }

    tsw_maputs(1,tsw_vsize,0x70,QString(' ',tsw_hsize));

    if(num_yells) tsw_changeatt(0xF0,1,tsw_vsize,tsw_hsize,tsw_vsize);

    switch(display_mode)
      {
       case 1: sprintf(s,"%s <%u>",user.name,user.level);
               tsw_mputs(2,tsw_vsize,s);
               if(sysop_next) tsw_changeatt(0xF0,1,tsw_vsize,strlen(s)+1,tsw_vsize);
               sprintf(s," [%ld bps]  [Online: %d]  [Left: %d]",io.baud,timer.online(),timer.left());
               tsw_mputs(tsw_hsize-strlen(s)-(rip_mode?2:0),tsw_vsize,s);
               if(rip_mode) tsw_maputc(tsw_hsize - 1,tsw_vsize,0xF0,'R');
               break;
       case 2: sprintf(s,"[Handle: %s]",user.alias);
               tsw_mputs(2,tsw_vsize,s);
               sprintf(s,"[Flags: ");
               user.aFlags.flagstostr(&s[8]);
               strcat(s,"]");
               tsw_mputs(tsw_hsize-strlen(s),tsw_vsize,s);
               break;
       case 3: sprintf(s,"[City: %s",user.city);
               if(user.country[0])
                 {
                  strcat(s,", ");
                  strcat(s,user.country);
                 }
               strcat(s,"]");
               tsw_mputs(2,tsw_vsize,s);
               sprintf(s,"[Data: %s]  [Tel: %s]",user.dataPhone,user.voicePhone);
               tsw_mputs(tsw_hsize-strlen(s),tsw_vsize,s);
               break;
       case 4: sprintf(s,"[#Calls: %ld]     [#DL: %ld]     [K DL: %ld]     [#UL: %ld]     [K UL: %ld]",user.timesCalled,user.numDownloads,user.kbDownloaded,user.numUploads,user.kbUploaded);
               tsw_centerline(tsw_vsize,s);
               break;
       case 5: sprintf(s,"[%s]",user.comment);
               tsw_centerline(tsw_vsize,s);
               break;
       case 6: sprintf(s,"[System calls: %ld]        [#Msgs: %ld]        [#Users: %d]",totalcalls,msgbase.totalMsgs(),num_users);
               tsw_centerline(tsw_vsize,s);
               break;
       case 7: sprintf(s,"[Chat: %s]",page_reason);
               tsw_centerline(tsw_vsize,s);
               break;
       case 8: sprintf(s,"[Last Caller: %s]",lastcaller.name);
               tsw_mputs(2,tsw_vsize,s);
               sprintf(s,"[%d-%s-19%d] [%02d:%02d-%02d:%02d]",lastcaller.date[0],months_short[lastcaller.date[1]],
                                                                   lastcaller.date[2],
                                                                   lastcaller.timeIn[0],lastcaller.timeIn[1],
                                                                   lastcaller.timeOut[0],lastcaller.timeOut[1]);
               tsw_mputs(tsw_hsize-strlen(s),tsw_vsize,s);
               break;
       case 9: sprintf(s,"[DOB: %02d-%s-%02d]   [Time used today: %ld]   [KBYTEs DL today: %d]",user.birthDate[0],months_short[user.birthDate[1]],user.birthDate[2],long(user.timeUsed+timer.used()),user.kbToday);
               tsw_centerline(tsw_vsize,s);
               break;
      }
    }
  else tsw_selbar(tsw_vsize,1,tsw_hsize,0x70);
}
*/

void
TpTimer::Decrease()
{
   suspendedtime--;

   Check();
}

void
TpTimer::Increase()
{
   suspendedtime++;

   Check();
}

TpTimer::TpTimer()
{
   started        = 0;
   suspended      = 0;
   suspendedtime  = 0;
   fixedtime      = 0;
}

void
TpTimer::Start(int min)
{
   started       = time(NULL);
   suspended     = FALSE;
   suspendedtime = 0;
   fixedtime     = 0;

   TimeLimit    = min;
}

void
TpTimer::Suspend()
{
   if(!suspended) suspend_start = time(NULL);

   suspended++;
}

void
TpTimer::Restart()
{
   if(!suspended) return;

   suspended--;

   if(!suspended)
      suspendedtime += int((time(NULL)-suspend_start)/60L);
}

int
TpTimer::Online()
{
   if(!started)
      return 0;
   else
      return (int)((time(NULL)-started)/60L);
}

int
TpTimer::Left()
{
   int x = TimeLimit - Online() + suspendedtime + fixedtime;

   if(suspended) x += int((time(NULL)-suspend_start)/60L);

   return x;
}

void
TpTimer::ChangeLeft(int l)
{
   fixedtime = l - TimeLimit - suspendedtime + Online();
}

int
TpTimer::Used()
{
   return Online() - suspendedtime;
}



void
TpTimer::Check()
{
   static bool warning = FALSE;

   if(!started) return;

   int l = Left();

   if(l>2) warning = FALSE;

   if(l<0)
   {
      io << '\n' << S_TIME_LIMIT_EXCEEDED << '\xFF';

      LOG("Time limit! User thrown out.");

      Delay(2000);

      throw TXQuit();
   }

   if(l<=2 && !warning)
   {
      io << '\7' << '\7' << '\n' << S_TIME_LIMIT_WARNING("2") << "\n\xFF";

      warning = TRUE;
   }
}

void
TpTimer::CheckInactivity()
{
   static bool warning = FALSE;

   if(!BaudRate || !cfg.inactivityTime) return;

   int inactive=(int)(time(NULL)-inactivity_start);

   if(inactive > cfg.inactivityTime+1000)
   {
      ClearInactivity();

      return;
   }

   if(inactive < cfg.inactivityTime-20)
   {
      warning = FALSE;
      return;
   }

   if(inactive >= cfg.inactivityTime)
   {
      io << '\n' << S_INACTIVITY_TIMEOUT(form("%d",cfg.inactivityTime)) << "\n\xFF";

      LOG("Inactivity. User thrown out.");

      Delay(2000);

      throw TXQuit();
   }

   if(warning) return;

   io << '\7';
   io << '\7' << '\n' << S_INACTIVITY_WARNING("20") << "\n\xFF";

   LOG(2,"Inactivity warning");

   warning = TRUE;
}

void
TpTimer::ClearInactivity()
{
   inactivity_start = (long)time(NULL);
}

