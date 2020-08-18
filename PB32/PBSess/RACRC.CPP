#include "proboard.hpp"

DWORD
RaCrc(char *s)
{
   char x[36];
   strcpy(x,s);
   strupr(x);

   return (s[0]) ? ~crc32(x) : 0;
}
