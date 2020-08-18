#include "proboard.hpp"

#include <io.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int
mWriteMsg(char *data)
{
   TpMessage msg;
   TpMsgArea ma;
   QString param[5];
   bool goodbye = FALSE;
   int cost=0;
   bool to_specified = FALSE;
   bool subj_specified = FALSE;
   char netmail_address[30] = "";

   ParseData(data,param);

   if(param[0][0]=='*')
      msg.setArea(user.msgArea);
   else
      msg.setArea(atoi(param[0]));

   if(!ma.read(msg.areaNum())) return 1;

   io << "\f\n" << S_WRITE_MESSAGE_TITLE(ma.name) << '\n';

   msg.to[0]=0;

   for(int i=0;i<5;i++)
      if(param[i][0]=='/')
         switch(toupper(param[i][1]))
         {
            case 'T':
               strcpy(msg.to,(char *)(param[i])+3);
               to_specified = TRUE;
               break;

            case 'S':
               strcpy(msg.subj,(char *)(param[i])+3);
               if(msg.subj[0])
               subj_specified = TRUE;
               break;

            case 'L':
               goodbye = TRUE;
               break;

            case 'N':
               strncpy(netmail_address,(char *)(param[i])+3,29);
               netmail_address[29] = '\0';
               break;
          }

   if(!user.CheckAccess(ma.writeLevel,ma.writeFlags,ma.writeFlagsNot) && !ma.sysopAccess())
   {
      io << '\n' << S_NOT_ALLOWED_TO_WRITE_IN_AREA << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

      return 1;
   }

   strcpy(msg.from,user.name);

   if(ma.flags == 3)
   {
      strcpy(msg.from,user.alias);
   }
   else
   {
      if(ma.flags && (ma.flags!=2 || user.alias[0]))
      {
         io << '\n';

         if(ma.flags > 1)
            io << S_ASK_WRITE_MSG_USING_YOUR_ALIAS;
         else
            io << S_ASK_WRITE_MSG_USING_AN_ALIAS;

         if(Ask(0))
         {
            if(ma.flags==2)
            {
               if(user.alias[0] == '\0') strcpy(user.alias,user.name);
               strcpy(msg.from,user.alias);
            }
            else
            {
               for(;;)
               {
                  TpUser tmpuser;

                  io << "\n\n" << S_ENTER_ALIAS_TO_USE;

                  Input(msg.from,35,INPUT_UPFIRST);
                  if(!msg.from[0]) return 1;
                  if(tmpuser.Search(msg.from,TRUE,FALSE,TRUE)) continue;
                  if(!tmpuser.Search(msg.from)) break;
               }
            }
         }

         io << '\n';
      }
   }

   if(!msg.to[0])
      for(;;)
      {
         TpUser tuser;

         if(ma.msgType != MSG_PVT && ma.msgKind != MSG_NET)
            io << '\n' << S_ENTER_ALL_IF_TO_EVERYONE << '\n';

         io << '\n' << S_WRITE_MSG_TO;

         Input(msg.to,35,INPUT_UPFIRST);

         if(!msg.to[0]) return 1;
         if(!strcmp(msg.to,"All")   && ma.msgKind!=MSG_NET && ma.msgType != MSG_PVT) break;
         if(!strcmp(msg.to,"Sysop") && ma.msgKind==MSG_LOCAL) break;

         if(ma.msgKind!=MSG_LOCAL) break;

         if(ma.flags==1) break;

         io << "\n\n\7" << S_SCANNING_USER_FILE << '\xFF';

         if(tuser.Search(msg.to)) break;

         if(ma.flags==2)
            if(tuser.Search(msg.to,TRUE,FALSE,TRUE)) break;

         bool found = tuser.Search(msg.to,FALSE,TRUE,FALSE);

         for(int count = 0;found && count<2;count++)
            found = tuser.SearchNext();

         if(count==1)
         {
            tuser.Search(msg.to,FALSE,TRUE,FALSE);

            io << "\n\n" << S_CONFIRM_WRITE_MESSAGE_TO(tuser.name);

            if(Ask(TRUE))
            {
               strcpy(msg.to,tuser.name);
               break;
            }
            else
            {
               io << '\n';
               continue;
            }
         }

         if(count>1)
         {
            EnableStop();

            io << "\n\n" << S_FUZZY_SEARCH_LIST_HEADER << '\n';

            LineCounter(2);

            found = tuser.Search(msg.to,FALSE,TRUE,FALSE);

            while(found)
            {
               if(!(tuser.uFlags & UFLAG_HIDDEN))
               io << form("\6 %-32.32s \5%-22.22s \2%-22.22s\n",tuser.name,tuser.city,tuser.country);
               if(OutputStopped || LineCounter()) break;

               found = tuser.SearchNext();
            }

            DisableStop();

            if(!found)
               io << S_FUZZY_SEARCH_LIST_FOOTER << '\n';

            continue;
         }

         io << S_USER_NOT_LOCATED << '\n';
      }

   if(!strcmpl(msg.to,"Sysop")) strcpy(msg.to,ma.sysop);

   if(to_specified)
      io << '\n' << S_WRITE_MSG_TO << msg.to;


   if(ma.msgKind==MSG_NET)
   {
      TpAKA a;
      a.read(ma.aka);
      char tmp[30];

      if(netmail_address[0])
      {
         int point;

         NodeListEntry ne;
         ne.zone  = a.zone;
         ne.net   = a.net;
         ne.node  = a.node;

         if((point=ReadNodeListEntry(ne,netmail_address)) < 0)
         {
            LOG("Unknown netmail address: %s",netmail_address);
            return 1;
         }

         msg.destZone = ne.zone;
         msg.destNet  = ne.net;
         msg.destNode = ne.node;
         msg.destPoint= point;
         msg.cost     = cost;
      }
      else
      {
         io << "\n\n" << S_ENTER_NETMAIL_ADDRESS_HEADER;

         for(;;)
         {
            int point;

            io << "\n\n" << S_ENTER_NETMAIL_ADDRESS;

            Input(tmp,25);
            if(!tmp[0]) return 1;
            io << "\n\n";

            NodeListEntry ne;

            ne.zone  = a.zone;
            ne.net   = a.net;
            ne.node  = a.node;

            if((point=ReadNodeListEntry(ne,tmp))<0) continue;

            cost=ne.cost;

            io << S_CONFIRM_NETMAIL_ADDRESS(form("%d:%d/%d.%d",ne.zone,ne.net,ne.node,point),ne.name,form("%d",ne.cost));

            if(Ask(1))
            {
               if(user.credit<cost)
               {
                  io << "\n\n" << S_NOT_ENOUGH_NETMAIL_CREDIT(form("%d",user.credit))
                           << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

                  return 1;
               }

               msg.destZone = ne.zone;
               msg.destNet  = ne.net;
               msg.destNode = ne.node;
               msg.destPoint= point;
               msg.cost     = cost;
               break;
            }
         }
      }

      if(user.CheckAccess(cfg.crashLevel,cfg.crashFlags))
      {
         io << "\n\n" << S_ASK_SEND_CRASH;

         if(Ask(0))
            msg.attr |= MSGATTR_CRASH;
      }

      if(user.CheckAccess(cfg.attachLevel,cfg.attachFlags))
      {
         io << "\n\n" << S_ASK_ATTACH_FILE;

         if(Ask(0))
         {
            msg.attr |= MSGATTR_FILE;
            io << "\n\n" << S_FILE_TO_ATTACH;
            Input(msg.subj,60);
            if(!msg.subj[0]) return 1;
         }
      }

      if(cfg.killSent)
         msg.attr |= MSGATTR_KILL;
   }

   if(subj_specified)
   {
      io << "\n\n" << S_SHOW_MESSAGE_SUBJECT(msg.subj);
   }
   else
   {
      if(!(msg.attr & MSGATTR_FILE))
      {
         io << "\n\n" << S_ENTER_MESSAGE_SUBJECT;

         Input(msg.subj,65);

         if(!msg.subj[0])
            return 1;
      }
   }

   switch(ma.msgType)
   {
      case MSG_BOTH:
         {
            if(strcmp(msg.to,"All"))
            {
               io << "\n\n" << S_ASK_PRIVATE_MESSAGE;
               if(Ask(0)) msg.attr |= MSGATTR_PRIVATE;
            }
         }
         break;

      case MSG_PVT:
         {
            msg.attr |= MSGATTR_PRIVATE;
         }
         break;

   }

   io << '\n';
   unlink("MSGTMP");

   WriteMSGINF( msg.from , msg.to , msg.subj , ma.highMsg()+1 , ma.name , (msg.attr & MSGATTR_PRIVATE) ? "YES":"NO");

   EditMessage();

   unlink("MSGINF");

   if(!access("MSGTMP",0))
   {
      io << "\n\n" << S_SAVING_MESSAGE;

      msg.postDate.today();
      msg.postTime.now();

      long nr = msg.add();

      if(nr >= 1)
      {
         nr = msg.msgBase()->msgNum(*msg.msgArea,nr);
      }

      if(nr<1)
      {
         io << S_SAVING_MESSAGE_ERROR << '\n';
      }
      else
      {
         io << form("\3#%d\n",nr);

         user.msgsPosted++;

         LOG(1,"Msg #%ld entered (Area %d)",nr,msg.areaNum());

         if(ma.msgKind == MSG_NET)
            user.pending += cost;
      }
   }
   else
   {
      LOG(1,"Msg aborted (Area %d)",msg.areaNum());
   }

   if(goodbye)
      mLogoff(NULL);
   else
      io << '\n' << S_PRESS_ENTER_TO_CONTINUE;

   return 0;
}

void
EditMessage()
{
   if((user.uFlags & UFLAG_FSED) && (Terminal() == Ansi || Terminal() == Avatar))
   {
      if(mRunPex("/I FSED") < 0)
      {
         if(!cfg.editorName[0] && !cfg.internalFsed)
         {
            InternalMsgEd();
            return;
         }

         QString editorcommand(cfg.editorName);

         if(cfg.internalFsed)
            editorcommand = "@_FSED";

         if(editorcommand[0] == '@')
         {
            editorcommand.del(0,1);
            mRunPex(ReplaceStringVars(editorcommand));
         }
         else
         {
            editorcommand << "*N*Q *P *B *T *I";
            mShell(ReplaceStringVars(editorcommand));
         }

         switch(ShellReturnCode)
         {
            case 1: io << "\n\n" << S_MESSAGE_ABORTED << '\n';
                    unlink("MSGTMP");
                    break;
            case 2: LOG("Carrier lost while editing.");
                    throw TXQuit();
         }
      }
   }
   else
   {
      InternalMsgEd();
   }
}

void
WriteMSGINF(char *from , char *to , char *subj , long num , char *area , char *pvt)
{
   QFile f;

   if(f.open("MSGINF",fmode_create | fmode_text))
   {
      f << from << '\n';
      f << to   << '\n';
      f << subj << '\n';
      f << form("%ld\n",num);
      f << area << '\n';
      f << pvt  << '\n';
   }
}
