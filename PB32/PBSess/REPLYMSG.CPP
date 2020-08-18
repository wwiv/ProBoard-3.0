#include "proboard.hpp"

#include <io.h>
#include <string.h>


void
ReplyMessage(TpMessage& orgmsg)
{
   TpMessage msg;
   TpMsgArea ma;

   bool diff_area = FALSE;

   strcpy(msg.to,orgmsg.from);
   strcpy(msg.from,user.name);
   strcpy(msg.subj,orgmsg.subj);

   ma = *orgmsg.msgArea;

   msg.setArea(ma.replyBoard);

   if(ma.replyBoard && ma.replyBoard != ma.areaNum) diff_area = TRUE;

   ma = *msg.msgArea;

   if(ma.flags == 3)
   {
      if(user.alias[0] == '\0') strcpy(user.alias,user.name);

      strcpy(msg.from,user.alias);
   }
   else
   {
      if(ma.flags && (ma.flags!=2 || user.alias[0]))
      {
         if(ma.flags == 2)
            io << "\n\n" << S_REPLY_TO_MSG_USING_YOUR_ALIAS;
         else
            io << "\n\n" << S_REPLY_TO_MSG_USING_AN_ALIAS;

         if(Ask(0))
         {
            if(ma.flags==2)
            {
               if(user.alias[0] == '\0') strcpy(user.alias,user.name);
               strcpy(msg.from,user.alias);
            }
            else
               for(;;)
               {
                  TpUser tmpuser;

                  io << "\n\n" << S_ENTER_ALIAS_TO_USE;

                  Input(msg.from,35);

                  if(!msg.from[0]) return;

                  if(tmpuser.Search(msg.from,TRUE,FALSE,TRUE)) continue;

                  if(!tmpuser.Search(msg.from)) break;
               }

            io << '\n';
         }
      }
   }

   io << "\n\n" << S_SHOW_MESSAGE_SUBJECT(msg.subj);

   io << "\n\n" << S_DO_YOU_WANT_TO_CHANGE_THE_SUBJECT;

   if(Ask(FALSE))
   {
      io << "\n\n" << S_ENTER_MESSAGE_SUBJECT;
      Input(msg.subj,63);
      if(!msg.subj[0]) return;
   }

   switch(ma.msgType)
   {
      case MSG_BOTH:
         {
            io << "\n\n" << S_ASK_PRIVATE_MESSAGE;

            if(Ask(0))
               msg.attr |= MSGATTR_PRIVATE;
         }
         break;

      case MSG_PVT:
         {
            msg.attr |= MSGATTR_PRIVATE;
         }
         break;
   }

   if(ma.msgKind==MSG_NET)
   {
      msg.destZone = orgmsg.origZone;
      msg.destNet  = orgmsg.origNet;
      msg.destNode = orgmsg.origNode;
      msg.destPoint= orgmsg.pointNum(0);

      if(user.CheckAccess(cfg.crashLevel,cfg.crashFlags))
      {
         io << "\n\n" << S_ASK_SEND_CRASH;

         if(Ask(0)) msg.attr |= MSGATTR_CRASH;
      }

      if(cfg.killSent)
         msg.attr |= MSGATTR_KILL;
   }

   unlink("MSGTMP");

   if((user.uFlags & UFLAG_FSED) && (user.uFlags && (UFLAG_ANSI|UFLAG_AVATAR)))
   {
      QString quote;

      io << "\n\n" << S_QUOTING_MESSAGE << '\xFF';

      if(!cfg.quoteString[0])
         strcpy(cfg.quoteString,">>");

      for(int i=0;i<strlen(cfg.quoteString);i++)
      {
         if(cfg.quoteString[i]=='@')
         {
            quote << orgmsg.from[0];

            for(int i=1;i<strlen(orgmsg.from);i++)
               if(orgmsg.from[i]==' ')
                  if(orgmsg.from[i+1])
                     quote << orgmsg.from[i+1];
         }
         else
         {
            quote << cfg.quoteString[i];
         }
      }

      quote << ' ';

      QFile tmpf;

      if(!tmpf.open("MSGTMP",fmode_create)) return;

      int inkludge=0;

      QString line;

      if((ma.msgKind==MSG_ECHO || ma.msgKind==MSG_PVTECHO)
         && strcmpl(orgmsg.to,user.name))

      tmpf << form("On <%s, %s>, %s wrote to %s :\r\n\r\n",
               (char *)orgmsg.postDate.format("DD MMM"),
               (char *)orgmsg.postTime.format("HH:MM"),
               orgmsg.from,
               orgmsg.to);

      int l = 255;

      for(long off=0;l==255;off+=255)
      {
         char s[256];

         l = orgmsg.readText(s,off,255);

         for(int j=0;j<l;j++)
         {
            BYTE x=s[j];

            if(x=='\n' || x==0x8D) continue;

            if(x==1) inkludge=1;

            if(x=='\r')
            {
               x='\n';

               if(inkludge)
               {
                  inkludge=0;

                  continue;
               }
            }

            if(inkludge) continue;

            if(x=='\n')
            {
               tmpf << quote << line << "\r\n";

               line="";

               continue;
            }

            line << char(x);

            if(line.len()>78-quote.len())
            {
               QString wrap;

               WordWrap(line,wrap,78-quote.len());

               tmpf << quote << line << "\r\n";

               line=wrap;
            }
         }
      }

      if(line.len()) tmpf << quote << line << "\r\n";

      tmpf.close();
   }

   WriteMSGINF( msg.from , msg.to , msg.subj , ma.highMsg()+1 , ma.name , (msg.attr & MSGATTR_PRIVATE) ? "YES":"NO");

   EditMessage();

   unlink("MSGINF");

   if(!access("MSGTMP",0))
   {
      io << "\n\n" << S_SAVING_MESSAGE;

      msg.postDate.today();
      msg.postTime.now();

      long nr=msg.add();

      if(nr >= 1)
      {
         nr = msg.msgBase()->msgNum(*msg.msgArea,nr);
      }

      if(nr<1)
      {
         io << S_SAVING_MESSAGE_ERROR;
      }
      else
      {
         io << form("\3#%d\n",nr);

         if(!diff_area) msg.addReply(orgmsg);

         user.msgsPosted++;

         LOG(1,"Msg #%ld entered (Reply to msg #%ld from %s)",msg.num,orgmsg.num,orgmsg.from);
      }
   }
   else
   {
      LOG(1,"Msg aborted. Reply to msg #%ld from %s",orgmsg.num,orgmsg.from);
   }
}

