#include "proboard.hpp"

#include <stdlib.h>
#include <string.h>


int
mReadMessages(char *data)
{
   TpMsgArea ma ,
             reply_area;
   long orgmsg = 0;
   QString param[10];
   int searchmethod = 0;
   int searchorder  = 0;
   char searchdata[80];
   long firstmsg=0;
   int area;
   bool inchain = FALSE;
   bool nonext  = FALSE;
   bool newmode = FALSE;

   TpMessage msg;

   TpMarkedMsgList marked = markedmsglist;

   ParseData(data,param);

   if(param[0][0]=='*')
      area = user.msgArea;
   else
      area = atoi(param[0]);

   if(area)
   {
      if(!ma.read(area)) return 1;

      if(!user.CheckAccess(ma.readLevel,ma.readFlags,ma.readFlagsNot) && !ma.sysopAccess())
      {
         io << "\n\n" << S_ACCESS_DENIED << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

         return 1;
      }

      long n = ma.MsgBase()->numMsgs(ma);

      if(n < 0)
      {
         io << '\n' << S_THIS_MESSAGE_AREA_IS_LOCKED << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

         return 1;
      }

      if(n)
      {
         io << '\n' << S_THERE_ARE_X_MESSAGES_IN_THIS_AREA(form("%d",n)) << '\n';
      }
      else
      {
         io << '\n' << S_THERE_ARE_NO_MESSAGES_IN_THIS_AREA <<
                    "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

         return 1;
      }

      msg.setArea(area);
   }


   if(param[1][0]=='/' && param[1][1]=='N')
   {
      searchmethod = READMSG_MARKED;
      searchorder  = +1;
   }
   else
   {
      QString hotkeys = K_READ_MESSAGES_ORDER_SELECTION;
      hotkeys << '\r';

      char key;

      if(area)
      {
         io << '\n';
         key = Send(S_READ_MESSAGES_ORDER_SELECTION,hotkeys);

         if(!key) key = WaitKeys(hotkeys);

         key = hotkeys.find(QString(char(key)));
      }
      else
      {
         key = 3;  // read new!
      }

      io << "\n\n";

      switch(key)
      {
         case 7  : return 0;

         case 1  : io << S_READMSG_FORWARD << '\n';
                   searchmethod = READMSG_ALL;
                   searchorder  = 1;
                   break;
         case 2  : io << S_READMSG_REVERSE << '\n';
                   searchmethod = READMSG_ALL;
                   searchorder  = -1;
                   break;
         case 0  : io << S_READMSG_ALL << '\n';
                   searchmethod = READMSG_ALL;
                   break;
         case 3  : io << S_READMSG_NEW << '\n';
                   searchmethod = READMSG_NEW;
                   searchorder  = 1;
                   break;
         case 4  :
            {
               io << S_READMSG_SELECTED;

               char k = WaitLanguageHotkeys(K_READMSG_SELECTED);

               if(k == '\r') return 0;

               io << K_READMSG_SELECTED[k];

               switch(k)
               {
                  case 0: k = 'F'; break;
                  case 1: k = 'T'; break;
                  case 2: k = 'S'; break;
                  case 3: k = 'E'; break;
               }

               searchdata[0] = k;

               io << "\n\n" << S_READMSG_SELECTED_SEARCH_FOR;

               Input(&searchdata[1],60,INPUT_UPALL);

               if(!searchdata[1]) return 0;

               searchmethod = READMSG_SEL;

               io << '\n';
            }
            break;

         case 5  : io << S_READMSG_INDIVIDUAL << '\n';
                   searchmethod = READMSG_INDIV;
                   searchorder  = 1;
                   break;
         case 6  : io << S_READMSG_MARKED << '\n';
                   searchmethod = READMSG_MARKED;
                   break;
      }

      if(!searchorder)
      {
         io << S_READMSG_ALL_FORWARD_OR_REVERSE;

         key = WaitLanguageHotkeys(K_READMSG_ALL_FORWARD_OR_REVERSE);

         if(key==1)
         {
            searchorder = -1;
            io << S_READMSG_REVERSE << '\n';
         }
         else
         {
            searchorder = +1;
            io << S_READMSG_FORWARD << '\n';
         }
      }

      if(area)
      {
         long highnum = ma.msgNum(ma.highMsg());
         long lownum  = ma.msgNum(ma.lowMsg());

         if(searchorder<0) firstmsg = highnum;
                  else     firstmsg = lownum;

         if(searchmethod != READMSG_MARKED && searchmethod != READMSG_INDIV && searchmethod != READMSG_NEW)
         {
            io << '\n' << S_READMSG_START_AT_MESSAGE;
            Input(firstmsg);

            if(firstmsg > highnum && searchorder < 0) firstmsg = highnum;
            if(firstmsg < lownum  && searchorder > 0) firstmsg = lownum;

            firstmsg = ma.msgId(firstmsg);

            io << '\n';
         }
      }
   }    // No "/N" parameter

   if(searchmethod == READMSG_NEW)
   {
      newmode = TRUE;

      marked.clear();

      io << '\n' << S_READMSG_SEARCHING_NEW_MESSAGES;

      GetNewMsgs(marked,area);

      if(!marked.numMarked())
      {
         io << "\n\n" << S_READMSG_NO_NEW_MESSAGES_FOUND <<
               "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

         return 0;
      }

      io << S_READMSG_X_NEW_MESSAGES_FOUND(form("%d",marked.numMarked())) << '\n';

      searchmethod = READMSG_MARKED;
   }

   if(searchmethod != READMSG_INDIV && searchmethod != READMSG_MARKED)
   {
      if(!msg.readFirst(searchmethod,searchorder,firstmsg,searchdata))
      {
         io << '\n' << S_READMSG_NO_MESSAGES_FOUND << "\n\n"
            << S_PRESS_ENTER_TO_CONTINUE;

         return 0;
      }

      nonext = TRUE;
   }

   int markedmsg_index = 0;

   bool continuous = FALSE;

   if(searchmethod!=READMSG_INDIV)
   {
      io << '\n' << S_READMSG_WAIT_AFTER_EACH_MSG;

      continuous = !Ask(1);

      if(continuous)
      {
         io << "\f\n\n" << S_PRESS_S_TO_STOP_OR_P_TO_PAUSE;
      }
   }


   for(;;)
   {
      if(searchmethod==READMSG_INDIV && !inchain)
      {
         long nr;

         io << "\n\n" << S_READMSG_INDIV_ASK_MSGNUM;

         if(Input(nr)<0) break;

         nr = ma.msgId(nr);

         if(!msg.read(nr))
         {
            io << "\n\n" << S_READMSG_INDIV_MSG_NOT_FOUND;

            continue;
         }

         io << '\n';
      }

      if(searchmethod == READMSG_MARKED && !inchain && !nonext)
      {
         if(markedmsg_index >= marked.numMarked()) break;

         TpMessageIndex mi = marked[markedmsg_index++];

         if(area)
            if(mi.area != area)
               continue;

         if(!msg.read(mi.num,mi.area))
            continue;
      }

      if(!area)
      {
         if(!ma.read(msg.areaNum())) continue;
      }

      if(nonext || inchain)
      {
         nonext = FALSE;
      }
      else
      {
         if(searchmethod!=READMSG_INDIV && searchmethod!=READMSG_MARKED)
            if(!msg.readNext(searchmethod,searchorder,searchdata))
               break;
      }

      if(orgmsg == msg.id) inchain = FALSE;

      if(!msg.readAccess()) continue;

      if((searchmethod!=READMSG_MARKED || ma.msgType==MSG_TOALL || newmode) && !inchain)
      {
         if(msg.id > ma.lastRead()) ma.setLastRead(msg.id);

         if(   int(msg.id) > user.highMsgRead
            && ma.areaNum <= 200
            && ma.msgBaseType == MSGBASE_HUDSON) user.highMsgRead = int(msg.id);
      }

      if(    !strcmpl(msg.to,user.name)
         || (!strcmpl(msg.to,user.alias) && ma.flags>0 && user.alias[0]))
      {
         if(!(msg.attr & MSGATTR_RECEIVED))
         {
            msg.setFlag(MSGATTR_RECEIVED);

            LOG(1,"Message #%ld received (area %d)",msg.num,msg.areaNum());
         }
      }
      else
      {
         LOG(2,"Message #%ld read (area %d)",msg.num,msg.areaNum());
      }

   again:
      OutputStopped=0;

      if(!(user.uFlags & UFLAG_CLEAR) || continuous)
      {
         io << '\n';

         if(LineCounter())
            OutputStopped = TRUE;

         io << '\n';

         if(LineCounter())
            OutputStopped = TRUE;
      }

      if(!continuous) io << '\f';

      if(!OutputStopped)
         switch(msg.show())
         {
            case 'N' :
            case '\r': continue;
            case 'S' : OutputStopped=1;
                       break;
            case 'A' : goto again;
         }

      if(continuous)
      {
         if(OutputStopped) break;

         continue;
      }

      QString optline("\n\6");
      QString hotkeys("?\r");

      int button_num = 0;

      if(!inchain)
      {
         optline << S_MSGPROMPT_NEXT << ' ';
         hotkeys << K_MSGPROMPT_NEXT;
      }

      if(searchmethod != READMSG_MARKED || markedmsg_index>1)
      {
         optline << S_MSGPROMPT_PREV << ' ';
         hotkeys << K_MSGPROMPT_PREV;
      }

      optline << S_MSGPROMPT_AGAIN << ' ' << S_MSGPROMPT_STOP << ' ' << S_MSGPROMPT_MARK << ' ';
      hotkeys << K_MSGPROMPT_AGAIN << K_MSGPROMPT_STOP << K_MSGPROMPT_MARK;

      reply_area = ma;

      if(ma.replyBoard)
         if(!reply_area.read(ma.replyBoard))
            reply_area = ma;

      if(user.CheckAccess(reply_area.writeLevel,reply_area.writeFlags,reply_area.writeFlagsNot) || reply_area.sysopAccess())
      {
         optline << S_MSGPROMPT_REPLY << ' ';
         hotkeys << K_MSGPROMPT_REPLY;
      }

      if(ma.sysopAccess() || !strcmpl(msg.from,user.name) || !strcmpl(msg.to,user.name))
      {
         optline << S_MSGPROMPT_UNREAD << ' ';
         hotkeys << K_MSGPROMPT_UNREAD;

         if(   ma.sysopAccess()
            || (ma.msgKind != MSG_ECHO)
            || (   ma.msgKind == MSG_ECHO
            && msg.attr & MSGATTR_UNSENT_ECHO
            && !strcmpl(msg.from,user.name)
               )
           )
         {
            optline << S_MSGPROMPT_DEL << ' ';
            hotkeys << K_MSGPROMPT_DEL;
         }
      }

      if(ma.sysopAccess())
      {
         optline << S_MSGPROMPT_SYSOPFUNC << ' ';
         hotkeys << K_MSGPROMPT_SYSOPFUNC;
      }

      if(inchain)
      {
         optline << S_MSGPROMPT_ORIG << ' ';
         hotkeys << K_MSGPROMPT_ORIG;
      }

      if(msg.next)
      {
         optline << "[+";
         if(msg.prev) optline << '/';
         hotkeys << '+';
      }
      else
      {
         if(msg.prev) optline << '[';
      }

      if(msg.prev)
      {
         optline << "-] ";
         hotkeys << '-';
      }
      else
      {
         if(msg.next) optline << "] ";
      }

      if(inchain)
         optline << "[?]: <\7" << K_MSGPROMPT_ORIG << "\6> \7";
      else
         optline << "[?]: <\7" << K_MSGPROMPT_NEXT << "\6> \7";

      char k = Send(optline,hotkeys);

      if(!k) k=WaitKeys(hotkeys);

      if(k=='\r')
         k = (inchain) ? K_MSGPROMPT_ORIG[0]:K_MSGPROMPT_NEXT[0];

      io << k;


      if(k==K_MSGPROMPT_STOP[0])
      {
         break;
      }

      if(k==K_MSGPROMPT_AGAIN[0])
      {
         goto again;
      }

      if(k==K_MSGPROMPT_REPLY[0])
      {
         ReplyMessage(msg);

         MenuStack.Update = TRUE;

         if(!msg.read(msg.id))
            continue;
         else
            goto again;
      }

      if(k==K_MSGPROMPT_DEL[0])
      {
         if(!ma.sysopAccess())
         {
            io << "\n\n" << S_ASK_DELETE_MSG;

            if(!Ask()) break;
         }

         LOG(1,"Msg #%ld deleted (area %d)",msg.num,msg.areaNum());

         msg.remove();

         if(inchain)
         {
            if(msg.read(orgmsg)) nonext = 1;
         }
         else
         {
            msg.readPrev(searchmethod,searchorder,searchdata);
         }

         inchain = FALSE;

         MenuStack.Update = TRUE;

         continue;
      }

      if(k == K_MSGPROMPT_MARK[0])
      {
         LOG(2,"Msg #%ld marked (area %d)",msg.num,msg.areaNum());

         markedmsglist.add(msg);

         io << "\n\n" << S_MESSAGE_MARKED
                 << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
      }

      if(k == K_MSGPROMPT_SYSOPFUNC[2])
      {
         msg.toggleFlag(MSGATTR_PRIVATE);

         msg.read(msg.id);

         goto again;
      }

      if(k==K_MSGPROMPT_SYSOPFUNC[0])
      {
         msg.forward();

         MenuStack.Update = TRUE;

         goto again;
      }

      if(k==K_MSGPROMPT_UNREAD[0])
      {
         msg.clearFlag(MSGATTR_RECEIVED);

         msg.read(msg.id);
      }

      if(k==K_MSGPROMPT_SYSOPFUNC[1])
      {
         msg.move();

         if(inchain)
         {
            if(msg.read(orgmsg))
               nonext = 1;
         }
         else
         {
            msg.readPrev(searchmethod,searchorder,searchdata);
         }

         inchain = FALSE;

         MenuStack.Update = TRUE;
      }

      if(k==K_MSGPROMPT_SYSOPFUNC[3])
      {
         char fn[50];

         io << "\n\n" << S_EXPORT_MESSAGE_TO_FILE;

         io << "\3";

         Input(fn,49,INPUT_UPALL);

         if(!fn[0]) goto again;

         io << '\n';

         msg.exportMsg(fn);

         goto again;
      }

      if(k==K_MSGPROMPT_PREV[0])
      {
         nonext = TRUE;

         if(searchmethod == READMSG_MARKED)
         {
            markedmsg_index -= 2;

            nonext = FALSE;

            continue;
         }

         for(;;)
         {
            if(msg.readPrev(searchmethod,searchorder,searchdata))
            {
               if(!msg.readAccess()) continue;

               break;
            }
            else
            {
               io << "\n\n" << S_THERE_IS_NO_PREVIOUS_MSG << ' ' << S_PRESS_ENTER_TO_CONTINUE;

               break;
            }
         }
      }

      if(k==K_MSGPROMPT_ORIG[0])
      {
         if(inchain)
            if(msg.read(orgmsg))
               nonext = TRUE;

         inchain = FALSE;
      }

      switch(k)
      {
         case '+':
            {
               if(!inchain) orgmsg = msg.id;

               for(;;)
               {
                  if(!msg.next)
                  {
                     io << "\n\n" << S_NO_ACCESS_TO_REPLIES
                             << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

                     if(msg.read(orgmsg)) nonext = TRUE;

                     inchain = FALSE;

                     break;
                  }

                  if(msg.read(msg.next))
                  {
                     if(!ma.read(msg.areaNum())) continue;

                     if(!msg.readAccess()) continue;

                     inchain = TRUE;

                     break;
                  }
                  else
                  {
                     if(msg.read(orgmsg))
                        nonext = TRUE;

                     inchain = FALSE;

                     break;
                  }
               }
            }
            break;

         case '-':
            {
               if(!inchain) orgmsg = msg.id;

               for(;;)
               {
                  if(!msg.prev)
                  {
                     io << "\n\n" << S_NO_ACCESS_TO_REPLIES
                             << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

                     if(msg.read(orgmsg)) nonext = TRUE;

                     inchain = FALSE;

                     break;
                  }

                  if(msg.read(msg.prev))
                  {
                     if(!msg.readAccess()) continue;

                     inchain = TRUE;
                     break;
                  }
                  else
                  {
                     if(msg.read(orgmsg)) nonext=1;
                     inchain=0;
                     break;
                  }
               }
            }
            break;

         case '?' :
            {
               if(ShowAnsiFile("MSGHELP",NULL)==SENDFILE_NOTFOUND)
               {
                  io << "\n\n\f" << S_MSGHELP_TITLE << "\n\n";

                  io << S_MSGHELP_NEXT    << '\n';
                  io << S_MSGHELP_PREV    << '\n';
                  io << S_MSGHELP_AGAIN   << '\n';
                  io << S_MSGHELP_STOP    << '\n';
                  io << S_MSGHELP_MARK    << '\n';
                  io << S_MSGHELP_REPLY   << '\n';
                  io << S_MSGHELP_DEL     << '\n';
                  io << S_MSGHELP_UNREAD  << '\n';
                  io << S_MSGHELP_PLUS    << '\n';
                  io << S_MSGHELP_MINUS   << '\n';
                  io << S_MSGHELP_ORIG    << '\n';

                  if(ma.sysopAccess())
                  {
                     io << S_MSGHELP_FORWARD << '\n';
                     io << S_MSGHELP_PRIVATE << '\n';
                     io << S_MSGHELP_MOVE    << '\n';
                     io << S_MSGHELP_EXPORT  << '\n';
                  }

                  io << '\n' << S_MSGHELP_NOTE    << '\n';

                  io << "\n\n" << S_PRESS_ENTER_TO_CONTINUE << '\n';
               }

               goto again;
            }
            break;

      } //case
   }// for

   io << "\n\n" << S_END_OF_MESSAGES
           << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

   return 0;
}

