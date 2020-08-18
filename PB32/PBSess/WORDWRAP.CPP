#include "proboard.hpp"

#include <string.h>


int
WordWrap(char *s,QString& str,int max)
{
   int spacepos=-1;

   if(strlen(s) <= unsigned(max)) return 0;

   for(int i=0;i<(int)strlen(s) && i<max;i++) if(s[i]==' ' || s[i]=='-') spacepos=i;

   if(spacepos<0)
   {
      str=&s[max];
      s[max]=0;
   }
   else
   {
      str=&s[spacepos+1];
      s[spacepos+1]=0;
   }

   return str.len();
}

