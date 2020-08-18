#include "proboard.hpp"

TpMarkedMsgList markedmsglist;

TpMarkedMsgList::TpMarkedMsgList()
{
 msgList = new TpMessageIndex[MAX_MARKED_MSGS];

 n = 0;
}

TpMarkedMsgList::TpMarkedMsgList(const TpMarkedMsgList &m)
{
 msgList = new TpMessageIndex[MAX_MARKED_MSGS];

 (*this) = m;
}

TpMarkedMsgList::~TpMarkedMsgList()
{
 delete [] msgList;
}

void
TpMarkedMsgList::operator=(const TpMarkedMsgList& m)
{
 for(int i=0 ; i < MAX_MARKED_MSGS ; i++) msgList[i] = m.msgList[i];

 n = m.n;
}

bool
TpMarkedMsgList::add(TpMessageIndex& mi)
{
 if(isMarked(mi)) return TRUE;

 if(n < MAX_MARKED_MSGS)
   {
    msgList[n++] = mi;

    return TRUE;
   }
  else
   {
    return FALSE;
   }
}

bool
TpMarkedMsgList::add(TpMessage& msg)
{
 return add(TpMessageIndex(msg.areaNum(),msg.id));
}

bool
TpMarkedMsgList::isMarked(TpMessageIndex& mi)
{
 for(int i=0 ; i<n ; i++)
   {
    if(msgList[i].num == mi.num && msgList[i].area == mi.area) return TRUE;
   }

 return FALSE;
}

void
TpMarkedMsgList::sort()
{
 int x,y;

 for(x=0;x<n-1;x++)
   for(y=x+1;y<n;y++)
     if(msgList[x].area > msgList[y].area)
       {
        TpMessageIndex tmp  = msgList[x];
               msgList[x] = msgList[y];
               msgList[y] = tmp;
       }

 for(x=0;x<n-1;x++)
   for(y=x+1;y<n;y++)
     if(msgList[x].area==msgList[y].area && msgList[x].num>msgList[y].num)
       {
        TpMessageIndex tmp  = msgList[x];
               msgList[x] = msgList[y];
               msgList[y] = tmp;
       }
}


void
GetNewMsgs(TpMarkedMsgList& marked,int area)
{
   TpMessage msg;
   TpMsgArea ma;

   io << ' ';

   int start = 1;
   int end   = 1000;

   if(area)
   {
      start = end = area;
   }

   for(int i=start ; i <= end ; i++)
   {
      if(   (area && area != i)
         || (!user.combinedBoards.connected(i) && !area)
         || !ma.read(i)
      ) continue;

      if(   !user.CheckAccess(ma.readLevel,ma.readFlags,ma.readFlagsNot)
         && !ma.sysopAccess()) continue;

      if(ma.highMsg() <= ma.lastRead()) continue;

      bool ok = msg.readFirst(READMSG_ALL,1,ma.lastRead() + 1,"",i);

      int cnt = 0;

      while(ok)
      {
         if(!marked.add(TpMessageIndex(msg.areaNum(),msg.id))) break;

         io << '\b' << (("/-\\|")[cnt]) ;

         cnt = (++cnt) % 4;

         ok = msg.readNext(READMSG_ALL,1,"");
      }

      if(ok) break;
   }

   io << "\b \b";
}
