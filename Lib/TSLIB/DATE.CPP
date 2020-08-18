/***************************************************************************
 class QDate
 class QTime

 Compatibility: DOS, OS/2, Windows
 Models       : 16/32 bit
***************************************************************************/

#include <ctype.h>
#include <time.h>
#include <dos.h>
#include <string.h>

#include "tslib.hpp"

const long JULIAN_ADJUSTMENT = 1721425L;


/////////////////////////////////////////////////////////////////////////////
// Calculates the number of days BEFORE the first of a given month         //
/////////////////////////////////////////////////////////////////////////////

static int
months_to_days(int month)
{
#ifdef PEX
   return int (l_div((l_mul(month , 3057) - 3007) , 100));
#else
   return int ((3057L * month - 3007) / 100);
#endif
}


/////////////////////////////////////////////////////////////////////////////
// Calculates the number of days in a given number of years since 1-1-0001 //
/////////////////////////////////////////////////////////////////////////////

static long
years_to_days(int yr)
{
#ifdef PEX
   return l_mul(yr , 365L) + yr / 4 - yr / 100 + yr / 400;
#else
   return yr*365L + yr/4 - yr/100 + yr/400;
#endif
}


QDate::QDate()
{
   _d = _m = _y = 0;
}

QDate::QDate(int d,int m,int y)
{
   _d = (unsigned short) d;
   _m = (unsigned short) m;

   if(y < 100)
      y += 1900;

   _y = (unsigned short) y;
}

QDate::QDate(const QDate& d)
{
   _d = d._d;
   _m = d._m;
   _y = d._y;
}

void
QDate::operator=(const QDate& d)
{
   _d = d._d;
   _m = d._m;
   _y = d._y;
}

QDate::QDate(long val)
{
   if(val < 0)
   {
      today();
   }
   else
   {
      (*this) = val;
   }
}

char *QDate::weekdays[7]   = { "Mon","Tue","Wed","Thu","Fri","Sat","Sun" };
char *QDate::s_weekdays[7] = { "Mo","Tu","We","Th","Fr","Sa","Su" };
char *QDate::l_weekdays[7] = { "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday" };
char *QDate::months[12]    = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
char *QDate::l_months[12]  = { "January","February","March","April","May","June","July","August","September","October","November","December" };

void
QDate::today()
{
   time_t tm_val = time(NULL);

   struct tm *tm_struct = localtime(&tm_val);

   _d = (unsigned short)(tm_struct->tm_mday);
   _m = (unsigned short)(tm_struct->tm_mon + 1);
   _y = (unsigned short)(tm_struct->tm_year+1900);
}

void
QDate::set(int day,int month,int year)
{
   _d = (unsigned short)(day);
   _m = (unsigned short)(month);
   _y = (unsigned short)((year<100) ? (year+1900) : year);
}

int
QDate::operator[](int i) const
{
   switch(i)
   {
      case 0 : return _d;
      case 1 : return _m;
      default: return _y;
   }
}

int
QDate::compare(const QDate& dt) const
{
   if(_y - dt._y) return (_y - dt._y);
   if(_m - dt._m) return (_m - dt._m);
   if(_d - dt._d) return (_d - dt._d);

   return 0;
}

int
QDate::operator<(const QDate& d) const
{
   return (compare(d) < 0);
}

int
QDate::operator>(const QDate& d) const
{
   return (compare(d) > 0);
}

int
QDate::operator==(const QDate& d) const
{
   return (compare(d) == 0);
}

int
QDate::operator!=(const QDate& d) const
{
   return compare(d);
}

int
QDate::operator>=(const QDate& d) const
{
   return (compare(d) >= 0);
}

int
QDate::operator<=(const QDate& d) const
{
   return (compare(d) <= 0);
}

bool
QDate::ok() const
{
   return bool(!(_d<1 || _m<1 || _m>12 || _y<0 || _d>daysInMonth()));
}

bool
QDate::leap() const
{
   return bool( _y%4 == 0 && _y%100 != 0 || _y%400 == 0 );
}

int
QDate::weekDay() const
{
   return int((long(*this)-1) % 7);
}

int
QDate::weekNum() const
{
   QDate nyd(1,1,_y);

   int w = (dayNum() + nyd.weekDay() - 1)/7 + (nyd.weekDay() < 4);

   return ((w < 1) ? weeksInYear(_y-1) : w);
}

int
QDate::weeksInYear(int y) const
{
   if(!y) y = _y;

   return QDate(31,12,y).weekNum();
}


QDate&
QDate::operator=(long julian)
{
   int n;                /* compute inverse of years_to_days() */

   for ( n = int((julian * 400L) / 146097L); years_to_days(n) < julian;) n++;

   _y = n - 1900;

   n = int(julian - years_to_days(n-1));

   if( n > 59 )
   {
      n += 2;

      if( leap() )  n -= (n > 62) ? 1 : 2;
   }

   _m = (unsigned short)((long(n) * 100 + 3007) / 3057);
   _d = (unsigned short)(n - months_to_days(_m));

   return *this;
}

int
QDate::dayNum() const
{
   int days = months_to_days(_m);

   if(_m>2)
   {
      days -= leap() ? 1:2;
   }

   return days + _d;
}

QDate::operator long() const
{
   return years_to_days(_y-1) + dayNum();
}

int
QDate::operator-(const QDate &d) const
{
   return int(long(*this) - long(d));
}


void
QDate::parse_key(QString& key) const
{
   int wd = weekDay();

   if(key == (char *)"D")    key = form("%d",_d);
   else
   if(key == (char *)"DD")   key = form("%02d",_d);
   else
   if(key == (char *)"WW")   key = s_weekdays[wd];
   else
   if(key == (char *)"WWW")  key = weekdays[wd];
   else
   if(key == (char *)"WWWW") key = l_weekdays[wd];
   else
   if(key == (char *)"M")    key = form("%d",_m);
   else
   if(key == (char *)"MM")   key = form("%02d",_m);
   else
   if(key == (char *)"MMM")  key = months[_m-1];
   else
   if(key == (char *)"MMMM") key = l_months[_m-1];
   else
   if(key == (char *)"YY")   key = form("%02d",_y % 100);
   else
   if(key == (char *)"CC")   key = form("%02d",_y/100);
}

QString
QDate::format(const char *fmt) const
{
   QString result , key;
   char last = *fmt;

   for( ; *fmt ; fmt++)
   {
      if(last != *fmt)
      {
         parse_key(key);

         result << key;

         key = *fmt;
      }
      else
      {
         key << *fmt;
      }

      last = *fmt;
   }

   parse_key(key);

   result << key;

   return result;
}

int
QDate::daysInMonth(int m) const
{
   static int months[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

   if(!m) m = _m;

   return months[m-1] + (leap() && m==2);
}

int
QDate::daysInYear(int y) const
{
   if(!y) y = _y;

   return 365 + QDate(1,1,y).leap();
}

int
QDate::age(const QDate& birthdate)
{
   int years = year() - birthdate.year();

   if((*this) < QDate(birthdate.day(),birthdate.month(),year()))
      years--;

   return years;
}


QTime::QTime()
{
   _h = _m = _s = 0;
}

QTime::QTime(const QTime& t)
{
   _h = t._h;
   _m = t._m;
   _s = t._s;
}

void
QTime::operator=(const QTime& t)
{
   _h = t._h;
   _m = t._m;
   _s = t._s;
}

void
QTime::set(int h,int m,int s)
{
    _h = BYTE(h);
    _m = BYTE(m);
    _s = BYTE(s);
}

void
QTime::now()
{
    time_t tm_val = time(NULL);

    struct tm *tm_struct = localtime(&tm_val);

    _h = BYTE(tm_struct->tm_hour);
    _m = BYTE(tm_struct->tm_min);
    _s = BYTE(tm_struct->tm_sec);
}

QTime::operator long() const
{
   return (long(_h) * 3600L) + (long(_m) * 60L) + long(_s);
}


long
QTime::operator-(const QTime& t) const
{
   return (long(*this) - long(t));
}

int
QTime::operator<(const QTime& t) const
{
    return ((*this - t) < 0);
}

int
QTime::operator>(const QTime& t) const
{
    return ((*this - t) > 0);
}

int
QTime::operator==(const QTime& t) const
{
    return ((*this - t) == 0);
}

int
QTime::operator!=(const QTime& t) const
{
    return ((*this - t) != 0);
}

int
QTime::operator>=(const QTime& t) const
{
    return ((*this - t) >= 0);
}

int
QTime::operator<=(const QTime& t) const
{
    return ((*this - t) <= 0);
}

char&
QTime::operator[](int i)
{
   switch(i)
   {
      case 0 : return _h;
      case 1 : return _m;
      default: return _s;
   }
}

void
QTime::operator+=(const QTime& t)
{
   (*this) = (long(*this) + long(t)) % 86400L;
}

void
QTime::operator-=(const QTime& t)
{
   (*this) = (long(*this) - long(t) + 86400L) % 86400L;
}

void
QTime::operator=(long l)
{
   _h = BYTE(l / 3600L);
   _m = BYTE((l % 3600L) / 60L);
   _s = BYTE(l % 60L);
}

void
QTime::parse_key(QString& key) const
{
   if(!strcmp(key,"H"))     key = form("%d",_h);
   else
   if(!strcmp(key, "HH"))   key = form("%02d",_h);
   else
   if(!strcmp(key,"h"))     key = form("%d",((_h+11) % 12) + 1);
   else
   if(!strcmp(key, "hh"))   key = form("%02d",((_h+11) % 12) + 1);
   else
   if(!strcmp(key, "MM"))   key = form("%02d",_m);
   else
   if(!strcmp(key, "SS"))   key = form("%02d",_s);
   else
   if(!strcmp(key, "PP"))   key = (_h >= 12) ? "PM":"AM";
   else
   if(!strcmp(key, "pp"))   key = (_h >= 12) ? "pm":"am";
   else
   if(!strcmp(key, "AA"))   key = (_h >= 12) ? "PM":"";
   else
   if(!strcmp(key, "aa"))   key = (_h >= 12) ? "pm":"";
   else
   if(!strcmp(key, "P"))    key = (_h >= 12) ? "P":"A";
   else
   if(!strcmp(key, "p"))    key = (_h >= 12) ? "p":"a";
   else
   if(!strcmp(key, "A"))    key = (_h >= 12) ? "P":"";
   else
   if(!strcmp(key, "a"))    key = (_h >= 12) ? "p":"";
}

QString
QTime::format(const char *fmt) const
{
   QString result , key;
   char last = *fmt;

   for( ; *fmt ; fmt++)
   {
      if(last != *fmt)
      {
         parse_key(key);

         result << key;

         key = *fmt;
      }
      else
      {
         key << *fmt;
      }

      last = *fmt;
   }

   parse_key(key);

   result << key;

   return result;
}

