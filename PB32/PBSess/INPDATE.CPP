#include "proboard.hpp"

#include <stdlib.h>
#include <ctype.h>

void
InputDate(QDate& d)
{
   char s[9];
   BYTE k;

   DrawField(8);

   int i=0;
   for(;;)
   {
      k = WaitKey();

      if((!isdigit(k) && k!=13 && k!=8) || k>0x7F)
         continue;

      if(k==8)
      {
         if(i>0)
         {
            i--;
            io << "\b \b";
            if(i==2 || i==5)
            {
               i--;
               io << "\b \b";
            }
         }

         continue;
      }

      if(k==13)
      {
         if(i==0)
         {
            d.set(0,0,0);
            break;
         }

         if(i!=8)
            continue;
         else
         {
            ParseDate(d,s,user.dateFormat);
            if(d.ok())
               break;
            else
               continue;
         }

      }

      if(i==8)
         continue;

      s[i++] = k;
      io << k;

      if(i==2 || i==5)
      {
         s[i++] = '/';
         io << '/';
      }
   }

   io << '\r';
   s[i]='\0';

   if(Terminal() == Avatar)
      io << char(22) << char(1) << char(CurrentAttribute() & 0x0F);
   else
      if(Terminal() == Ansi) io << "\x1b[40m";

   FlushOutput();
}


void
ParseDate(QDate& d , char *s , int format)
{
   char str[9];

   strncpy(str,s,8);
   str[8] = '\0';

   char *fmt = DateFormats[format];

   int fmt_ar[3];

   if(toupper(fmt[0] == 'D')) fmt_ar[0] = 0;
   if(toupper(fmt[0] == 'M')) fmt_ar[0] = 1;
   if(toupper(fmt[0] == 'Y')) fmt_ar[0] = 2;
   if(toupper(fmt[3] == 'D')) fmt_ar[1] = 0;
   if(toupper(fmt[3] == 'M')) fmt_ar[1] = 1;
   if(toupper(fmt[3] == 'Y')) fmt_ar[1] = 2;
   if(toupper(fmt[6] == 'D')) fmt_ar[2] = 0;
   if(toupper(fmt[6] == 'M')) fmt_ar[2] = 1;
   if(toupper(fmt[6] == 'Y')) fmt_ar[2] = 2;

   d.set(0,0,0);

   s = strtok(str, "-/.");
   if(s)
   {
	  int _d[3];

      _d[fmt_ar[0]] = atoi(s);
      s = strtok(NULL, "-/.");
      _d[fmt_ar[1]] = atoi(s);
      s = strtok(NULL, "-/.");
      _d[fmt_ar[2]] = atoi(s);

	  d.set(_d[0],_d[1],_d[2]);
   }
}
