#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <tslib.hpp>

#include "pblib.hpp"

#ifndef max
 #define max(a,b) (((a)>(b)) ? (a) : (b))
 #define min(a,b) (((a)<(b)) ? (a) : (b))
#endif


TpCombinedType::TpCombinedType()
{
 for(int i=0;i<125;i++) bits[i] = 0xFF;
}

bool
TpCombinedType::connected(int brdnr)
{
 if(brdnr < 1 || brdnr > 1000) return false;

 brdnr--;
 return (bits[brdnr/8] & (1<<(brdnr%8))) ? true : false;
}

void
TpCombinedType::connect(int brdnr)
{
   if(brdnr < 1 || brdnr > 1000) return;

   brdnr--;
   bits[brdnr/8] |= (1 << (brdnr%8));
}

void
TpCombinedType::disconnect(int brdnr)
{
   if(brdnr < 1 || brdnr > 1000) return;

   brdnr--;
   bits[brdnr/8] &= ~(1 << (brdnr%8));
}

void
TpCombinedType::toggle(int brdnr)
{
   if(brdnr < 1 || brdnr > 1000) return;

   if(connected(brdnr))
      disconnect(brdnr);
   else
      connect(brdnr);
}

bool
TpAccessFlags::getflag(int flagnr)
{
   return ((v&(1L<<(32-flagnr)))?1:0);
}

void
TpAccessFlags::setflag(int flagnr)
{
   v |= 1L << (32-flagnr);
}

void
TpAccessFlags::clearflag(int flagnr)
{
   v &= ~(1L << (32-flagnr));
}

void
TpAccessFlags::flagstostr(char *str)
{
   for(int i=1;i<=32;i++)
   {
      if(i>26)
         *str++ = getflag(i) ? char(i-27+'1') : '-';
      else
         *str++ = getflag(i) ? char(i-1 +'A') : '-';
   }

   *str = 0;
}

TpTimeFrame::TpTimeFrame()
{
   clear();
}

void
TpTimeFrame::clear()
{
   memset(periods , 0, sizeof(periods));
}

void
TpTimeFrame::setAll()
{
   memset(periods , 0xFF, sizeof(periods));
}

bool
TpTimeFrame::enabled() const
{
   return enabled(QDate(TODAY),QTime(NOW));
}

bool
TpTimeFrame::enabled(QTime& time) const
{
   return enabled(QDate(TODAY), time);
}

bool
TpTimeFrame::enabled(QDate& date,QTime& time) const
{
   return enabled(date.weekDay() , time);
}

bool
TpTimeFrame::enabled(int dow,QTime& time) const
{
   return enabled(dow,(time[0] * 60 + time[1]) / 30);
}

bool
TpTimeFrame::enabled(int dow,int period) const
{
   return (periods[dow][period/8] & (1<<(period%8))) ? true : false;
}

void
TpTimeFrame::enable(int dow,QTime& time)
{
   enable(dow,(time[0] * 60 + time[1]) / 30);
}

void
TpTimeFrame::enable(int dow,int period)
{
   periods[dow][period/8] |= (1 << (period%8));
}

void
TpTimeFrame::disable(int dow,QTime& time)
{
   disable(dow,(time[0] * 60 + time[1]) / 30);
}

void
TpTimeFrame::disable(int dow,int period)
{
   periods[dow][period/8] &= ~(1 << (period%8));
}
