#include "proboard.hpp"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

long TpMessage::lastIndex = -1;

TpMessage::TpMessage(int n)
{
 clear();

 msgArea = new TpMsgArea();

 if(n) msgArea->read(n);
}

TpMessage::TpMessage(TpMessage *p,int n)
{
 if(p != this) memcpy(this,p,sizeof(*p));

 msgArea = new TpMsgArea;

 if(n) msgArea->read(n);
}

void
TpMessage::clear()
{
 TpMsgArea *ma = msgArea;

 CLEAR_OBJECT(*this);

 msgArea = ma;
}

TpMessage::~TpMessage()
{
 delete msgArea;
}

bool
TpMessage::readAccess()
{
   if(!user.CheckAccess(msgArea->readLevel,msgArea->readFlags,msgArea->readFlagsNot) && !msgArea->sysopAccess())
      return FALSE;

   if(attr & MSGATTR_PRIVATE)
   {
     return !(   strcmpl(to,user.name)
              && strcmpl(from,user.name)
              && (strcmpl(to,user.alias) || !msgArea->flags)
              && (strcmpl(from,user.alias) || !msgArea->flags)
              && !msgArea->sysopAccess()
             );
   }
   else
   {
      return TRUE;
   }
}

int
TpMessage::areaNum()
{
 return msgArea->areaNum;
}

bool
TpMessage::setArea(int n)
{
 bool r = msgArea->read(n);

 if(!r) msgArea->areaNum = 0;

 return r;
}

bool
TpMessage::read(long n,int a)
{
 if(a) if(!msgArea->read(a)) return FALSE;

 long actual_n = msgBase()->readMsg(*this,n);

 return (n == actual_n) ? TRUE:FALSE;
}

void
TpMessage::setFlag(DWORD msgflag)
{
 if(msgflag & MSGATTR_RECEIVED)
   {
    recvDate.today();
    recvTime.now();
   }

 attr |= msgflag;

 msgBase()->updateMsg(*this);
}

void
TpMessage::clearFlag(DWORD msgflag)
{
 attr &= ~msgflag;

 msgBase()->updateMsg(*this);
}

void
TpMessage::toggleFlag(DWORD msgflag)
{
 attr ^= msgflag;

 msgBase()->updateMsg(*this);
}


void
TpMessage::addOrigin()
{
   TpAKA a;
   bool echo_area = FALSE;

   QFile fo,fi("MSGTMP",fmode_text);

   if(!fi.opened()) return;

   fo.open("MSGTMP.$$$",fmode_create|fmode_text);

   if(msgArea->msgKind == MSG_NET)
   {
       a.read(msgArea->aka);

       origZone  = a.zone;
       origNet   = a.net;
       origNode  = a.node;
       origPoint = a.point;

       if(msgArea->msgBaseType != MSGBASE_JAM)
       {
         if(origPoint) fo << form("\1FMPT %d\n",origPoint);
         if(destPoint) fo << form("\1TOPT %d\n",destPoint);
       }
   }

   if(msgArea->msgKind == MSG_ECHO || msgArea->msgKind == MSG_PVTECHO)
   {
       a.read(msgArea->aka);

       origZone   = destZone  = a.zone;
       origNet    = destNet   = a.net;
       origNode   = destNode  = a.node;
       origPoint  = destPoint = a.point;

       echo_area = TRUE;
   }

 bool blankline = false;

 for(;;)
 {
   QString line , copiedline;

   line = fi.readLine();

   if(line[0] == '\0') break;

   line.delLast('\n');

   copiedline = line;

   copiedline.trim();

   if(line.len() >= 4)
   {
      if(!strncmp(copiedline,"--- ",4))     break;  // Get rid of tagline
      if(!strncmp(copiedline,"* Origin",8)) break;  // Stop when *Origin found
   }

   if(!strcmp (copiedline,"---"))
      line.clear();

   if(line[0] != '\x01')
      fo << line << '\n';

   blankline = (line[0] == '\0');
 }

   if(!registered && (PastFirstUse < 0 || PastFirstUse > 60))
   {
      if(PastFirstUse < 0)
         PastFirstUse = 61;

      if(!blankline)
         fo << '\n';

      char *unr_str = "...This copy of ProBoard has been unregistered for %d days!\n\n";

      if(crc32(unr_str) != 0xB3328DC5L)
         throw TXQuit();

      fo << form(unr_str,PastFirstUse);

      blankline = TRUE;
   }

 if(echo_area)
 {
   if(!blankline)
      fo << '\n';

   fo << "--- ProBoard v" VERSION;

   if(registered)
      fo << " [Reg]";
   else
      fo << " [EVALUATION]";

   fo << "\n * Origin: ";

   if(msgArea->origin[0]) fo << msgArea->origin;
               else      fo << cfg.originLine;

   fo << form(" (%d:%d/%d",a.zone,a.net,a.node);

   if(a.point) fo << form(".%d)\n",a.point);
         else  fo << ")\n";
 }

 fo.close();
 fi.close();

 unlink("MSGTMP");
 rename("MSGTMP.$$$","MSGTMP");
}

long
TpMessage::add()
{
 attr |= MSGATTR_LOCAL;

 switch(msgArea->msgKind)
 {
   case MSG_NET     : attr |= MSGATTR_NETMAIL;
                      break;
   case MSG_PVTECHO :
   case MSG_ECHO    : attr |= MSGATTR_ECHOMAIL;
                      break;
 }


 addOrigin();

 if(msgArea->tag[0])
 {
    QFile f(QFileName(SysPath,"ECHOTOSS.LOG") , fmode_text | fmode_copen | fmode_rw | fmode_append);

    if(f.opened())
        f << msgArea->tag << '\n';
 }

 long n = msgBase()->appendMsg(*this);

 if(n < 1) return -1;

 /*
 switch(msgArea->msgKind)
 {
   case MSG_NET     : NetMailEntered++;
                      break;
   case MSG_PVTECHO :
   case MSG_ECHO    : EchoMailEntered++;
                      break;
 }
 */

 return n;
}

void
TpMessage::addReply(TpMessage& org)
{
 TpMessage msg(org.areaNum());

 long n = org.id;

 if(!msg.read(n)) return;

 while(msg.next) if(!msg.read(msg.next)) break;

 prev = msg.id;

 msgBase()->updateMsg(*this);

 msg.next = id;

 msg.msgBase()->updateMsg(msg);
}


void
TpMessage::delReply()
{
 TpMessage msg(areaNum());

 if(prev)
   {
    if(msg.read(prev))
      {
       msg.next = next;

       msg.msgBase()->updateMsg(msg);
      }
   }

 if(next)
   {
    if(msg.read(next))
      {
       msg.prev = prev;

       msg.msgBase()->updateMsg(msg);
      }
   }

 if(next || prev)
   {
    next = prev = 0;

    msgBase()->updateMsg(*this);
   }
}


int
TpMessage::pointNum(int mode)
{
   if(msgArea->msgBaseType != MSGBASE_HUDSON)
   {
      if(mode)
         return destPoint;
      else
         return origPoint;
   }

   QString s;
   int inkludge=0;
   bool msgdone = FALSE;

   for(long txt_off = 0; !msgdone ; txt_off += 255)
   {
      char rec[256];

      int l = readText(rec,txt_off,255);

      if(l < 255) msgdone = TRUE;

      for(int j=0;j < l;j++)
      {
         switch(rec[j])
         {
            case '\n': break;
            case '\r':
               {
                   if(inkludge)
                     {
                      s.upperCase();
                      if(mode)
                        {
                         if(!strncmp(s,"TOPT",4)) return atoi(&s[5]);
                        }
                       else
                        {
                         if(!strncmp(s,"FMPT",4)) return atoi(&s[5]);
                        }
                      }
                   inkludge=0;
                   s="";
                   } break;
        case   1 : {
                   s="";
                   inkludge=1;
                   } break;
        default  : if(inkludge) s << char(rec[j]);
                   break;
        }
      }
   }

   return 0;
}


QString
MSGTMPName()
{
   return QString("MSGTMP");
}


void
WriteMSGTMP(char *s)
{
   QFile f(MSGTMPName(),fmode_create);

   f << s;
}


