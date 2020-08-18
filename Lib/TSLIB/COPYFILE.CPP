/***************************************************************************
 class DirScan

 Compatibility: DOS, OS/2, Windows
 Models       : 16 bit only !
***************************************************************************/
#ifdef PEX
   #include <pb_sdk.h>
#else
   #include <io.h>
#endif

#include "tslib.hpp"

long
ts_CopyFile(char *from,char *to,int bufsize)
{
   QFileName fni,fno;

   fni = from;

   fno = to;

   fno.delLast('\\');

   if(ts_DirExists(fno))
   {
      QFileName tmp = fni;
      tmp.stripPath();

      fno << '\\' << tmp;
   }

   QFile fi,fo;

   BYTE *buf;
   long totalbytes = 0;

   buf = new BYTE[bufsize];

   if(buf == NULL) return -1;

   if(!fi.open(fni,fmode_read))
   {
      delete [] buf;

      return -1;
   }

   if(!fo.open(fno,fmode_create|fmode_write))
   {
      delete [] buf;

      return -1;
   }

   for(;;)
   {
      unsigned bytesread = fi.read(buf,bufsize);

      if(bytesread < 1) break;

      totalbytes += bytesread;

      if(fo.write(buf,bytesread) != bytesread)
      {
         totalbytes = -1;
         break;
      }
   }

   fi.close();
   fo.close();

   delete [] buf;

   ts_SyncFileDate(fni,fno);

   return totalbytes;
}
