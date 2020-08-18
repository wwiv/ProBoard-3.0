#include "proboard.hpp"


bool
TpMessage::readFirst(int method,int order,long first,char *data,int area)
{
   if(area)
   {
      if(!setArea(area)) return FALSE;
   }

   if(order<0)
   {
      lastIndex = first + 1;
   }
   else
   {
      lastIndex = (first > 0) ? (first - 1) : 0;
   }

   return readNext(method,order,data);
}

bool
TpMessage::readNext(int method,int order,char *data)
{
   for(lastIndex += order ; lastIndex ; lastIndex+=order)
   {
      lastIndex = msgBase()->readMsg(*this,(order<0) ? (-lastIndex) : (lastIndex));

      if(lastIndex < 0) break;

      switch(method)
      {
         case READMSG_ALL:
         {
            return TRUE;
         }

         case READMSG_SEL:
         {
            QString tofind = &data[1];

            switch(data[0])
            {
               case 'F': if(QString(from).find(tofind) >= 0) return TRUE;
                         break;
               case 'T': if(QString(to).find(tofind) >= 0)   return TRUE;
                         break;
               case 'S': if(QString(subj).find(tofind) >= 0) return TRUE;
                         break;
               case 'E': if(QString(from).find(tofind)>=0 || QString(to).find(tofind)>=0) return TRUE;
                         break;
            }
         }
         break;
      }
   }

   return FALSE;
}

bool
TpMessage::readPrev(int method,int order,char *data)
{
   long prevlast=lastIndex;

   bool x = readNext(method,-order,data);

   if(!x) lastIndex = prevlast;

   return x;
}

