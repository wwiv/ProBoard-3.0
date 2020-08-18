#include "proboard.hpp"

#include <string.h>


bool
TpAKA::read(int n)
{
   QFile f(QFileName(SysPath,"AKA.PB"));

   if(!f.opened())
   {
      CLEAR_OBJECT(*this);

      return false;
   }

   CLEAR_OBJECT(*this);

   f.seek(long(n)*sizeof(TpAKA));

   if(f.read(this,sizeof(TpAKA)) != sizeof(TpAKA))
   {
      CLEAR_OBJECT(*this);

      return false;
   }

   return TRUE;
}

