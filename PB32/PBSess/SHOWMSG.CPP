#include "proboard.hpp"

#include <ctype.h>
#include <string.h>


#define SEND_HEADER_LINE()         \
    {                              \
     k = Send(s,hotkeys);          \
     switch(k)                     \
       {                           \
       case 0:  break;             \
       case 1:  return 'S';        \
       default: return k;          \
       }                           \
     if(LineCounter()) return 'S'; \
     s.clear();                    \
    }

BYTE
TpMessage::show()
{
   char *hotkeys="AN\r";
   QString s;
   char k;

   s << '\r' << S_MSGHEADER_MESSAGENUM(form("%ld",msgNum()),msgArea->name) << " \7";

   if(attr & MSGATTR_PRIVATE) s << S_MSGHEADER_PRIVATE << ' ';

   if(msgArea->msgKind == MSG_NET)
   {
      if(attr & MSGATTR_CRASH) s << S_MSGHEADER_CRASH << ' ';
      if(attr & MSGATTR_KILL)  s << S_MSGHEADER_KILL << ' ';
      if(attr & MSGATTR_FILE)  s << S_MSGHEADER_FILE << ' ';
      if(attr & MSGATTR_SENT)  s << S_MSGHEADER_SENT << ' ';
   }


   if(prev) s << form("\7[%ld <ÄÄ] ",msgArea->msgNum(prev));
   if(next) s << form("\7[ÄÄ> %ld] ",msgArea->msgNum(next));

   s << '\n';

   SEND_HEADER_LINE();

   QString org(from);
   QString rip_org(from);
   QString dest(to);
   QString rip_dest(to);

   org << "\7";
   dest << "\7";

   if(msgArea->msgKind == MSG_NET)
   {
      int pt_from = pointNum(0);
      int pt_to   = pointNum(1);

      org << form(" (%d:%d/%d",origZone,origNet,origNode);
      dest << form(" (%d:%d/%d",destZone,destNet,destNode);

      if(pt_from) org  << form(".%d",pointNum(0));
      if(pt_to)   dest << form(".%d",pointNum(1));

      org  << ')';
      dest << ')';
   }

   s << S_MSGHEADER_FROM( (char *)org,
                          (char *)postDate.format(DateFormats[user.dateFormat]),
                          (char *)postTime.format("HH:MM")
                        ) << '\n';


   SEND_HEADER_LINE();

   s << S_MSGHEADER_TO((char *)dest) << ' ';

   if(attr & MSGATTR_RECEIVED)
   {
      if(recvDate.ok())
         s << S_MSGHEADER_RECEIVED_ON(
                        (char *)recvDate.format(DateFormats[user.dateFormat]),
                        (char *)recvTime.format("HH:MM")
                        );
      else
         s << S_MSGHEADER_RECEIVED;
   }

   s << '\n';

   SEND_HEADER_LINE();

   if(attr & MSGATTR_FILE)
      s << S_MSGHEADER_FILEATTACHED(subj) << '\n';
   else
      s << S_MSGHEADER_SUBJECT(subj) << '\n';

   SEND_HEADER_LINE();

   s << "\n\7";

   SEND_HEADER_LINE();

   s = "";

   io << "\7";

   int inkludge=0;

   QString wrap;

   int inquote=0;
   int index=0;

   char line[100];
   memset(line,0,100);

   bool msgdone = FALSE;

   for(long txt_off = 0; !msgdone ;txt_off += 255)
   {
      char r[256];

      int l = msgBase()->readMsgText(*this,r,txt_off,255);

      if(l < 255) msgdone = TRUE;

      for(int j=0;j<l;j++)
      {
         BYTE x=toupper(ReadKey());

         switch(x)
         {
            case 'S' :
            case 'N' :
            case '\r': return x;
            case 'P' : WaitKeys("P\r");
         }

         x = r[j];

         if(x == '\t') x = ' ';

         if(x == 1) inkludge=1;

         if(x == '\n' || x == 0x8D || x <= 8) continue;

         if(x == '\r')
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
            inquote=0;
            for(int i=0;i<6 && i<index;i++) if(line[i]=='>') inquote=1;
            if(inquote)
            {
               if(Terminal() == Avatar)
                  io << char(22) << char(1) << char(0xB);
               else
                  if(Terminal() == Ansi)
                     io << "[36m";
            }

            if(strncmp(line,"SEEN-BY",7))
            {
               io << line << '\n';

               if(LineCounter()) return 'S';
            }
            if(inquote)
            {
               if(Terminal() == Avatar)
                  io << char(22) << char(1) << char(0xF);
               else
                  if(Terminal() == Ansi)
                     io << "[37m";
            }

            memset(line,0,100);

            index=0;
         }
         else
         {
            if(x>=' ' || x==0x1B) line[index++] = x;
         }

         if(index>79)
         {
            WordWrap(line,wrap,79);

            if(strncmp(line,"SEEN-BY",7))
            {
               io << line << '\n';

               if(LineCounter()) return 'S';
            }

            memset(line,0,100);

            strcpy(line,wrap);

            index=strlen(line);
         }
      }
   }

   if(index)
      if(strncmp(line,"SEEN-BY",7))
      {
        io << line << '\n';

        if(LineCounter()) return 'S';
      }

   return 0;
}

