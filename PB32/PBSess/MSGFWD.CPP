#include "proboard.hpp"

#include <string.h>

void
TpMessage::forward()
{
 int areanum = 0;
 TpMsgArea ma;
 char newto[36];

 if(msgArea->msgKind == MSG_LOCAL) io << "\n\n" << S_FORWARD_IN_SAME_AREA;

 if(msgArea->msgKind != MSG_LOCAL || !Ask(TRUE))
   {
    io << "\n\f\n";
    LineCounter(0);
    mSelectMessageArea("* -N /L");
    io << '\n' << S_SELECT_MSG_AREA_TO_FORWARD_MESSAGE_IN;
    Input(areanum,5);

    if(areanum < 1) return;
   }
  else areanum = areaNum();


   if(!ma.read(areanum))
   {
      io << "\n\n" << S_UNKNOWN_MESSAGE_AREA
         << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

      return;
   }


 for(;;)
   {
    TpUser tuser;

    io << "\n\n" << S_FORWARD_MESSAGE_TO;

    Input(newto,35,INPUT_UPFIRST);

    if(!newto[0]) return;

    if(!strcmpl(newto,"Sysop")) strcpy(newto,msgArea->sysop);

    if(ma.msgKind != MSG_LOCAL || tuser.Search(newto)) break;

    io << "\n\n" << S_USER_NOT_LOCATED << '\n';
   }

 io << "\n\n" << S_FORWARDING_MESSAGE;

 QFile tmpf;
 if(!tmpf.open("MSGTMP",fmode_create)) return;

 tmpf << "----------------------------------------------------------------------\r\n";
 tmpf << form(" ** Original message to     : %s\r\n\r\n",to);
 tmpf << form(" ** Original post date/time : %d-%s-%02d  %02d:%02d\r\n\r\n",postDate.format(DateFormats[user.dateFormat]),postTime.format("HH:MM"));
 tmpf << form(" ** Forwarded by %s using ProBoard v" VERSION "\r\n",user.name);
 tmpf << "----------------------------------------------------------------------\r\n\r\n";

 tmpf.close();

 createMsgTextFile("MSGTMP",TRUE);

 if(PostMessage(from,newto,subj,areanum,(attr & MSGATTR_PRIVATE) ? TRUE : FALSE)<0)
   {
    io << S_SAVING_MESSAGE_ERROR;
   }

 io << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
}

