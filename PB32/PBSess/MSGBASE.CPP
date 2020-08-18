#include "proboard.hpp"


TpMsgBaseList::TpMsgBaseList()
{
    mblist[0] = NULL;
}

void
TpMsgBaseList::add(TpMsgBase *mb)
{
	int i;

   for(i=0; mblist[i] ; i++) {}

   mblist[i] = mb;
   mblist[i+1] = NULL;
}

TpMsgBaseList::~TpMsgBaseList()
{
    for(int i=0; mblist[i] ; i++) delete mblist[i];
}

void
TpMsgBaseList::open()
{
    for(int i=0 ; mblist[i] ; i++) mblist[i]->open();
}

void
TpMsgBaseList::close()
{
    for(int i=0 ; mblist[i] ; i++) mblist[i]->close();
}

bool
TpMsgBaseList::lock()
{
    for(int i=0 ; mblist[i] ; i++)
      if(!mblist[i]->lock())
         return false;

    return true;
}

bool
TpMsgBaseList::unlock()
{
    for(int i=0 ; mblist[i] ; i++)
      if(!mblist[i]->unlock())
         return false;

    return true;
}

unsigned
TpMsgBaseList::scanMail(TpMessageIndex *mi,unsigned maxmsgs,_TpUser& user)
{
   unsigned left = maxmsgs;

 	for(int i=0; mblist[i] ; i++)
   {
      if(left>0) left -= mblist[i]->scanMail(&mi[maxmsgs-left],left);
   }

 	return maxmsgs-left;
}

long
TpMsgBaseList::totalMsgs()
{
 long total = 0;

 for(int i=0; mblist[i] ; i++)
   {
    total += mblist[i]->totalMsgs();
   }

 return total;
}
