#include "proboard.hpp"

#include <direct.h>
#include <ctype.h>
#include <io.h>
#include <stdlib.h>

const WORD copy_bufsize = 16384;

/*
bool
copy_file( char *s , char *d )
{
   File fi,fo;

   if(!fi.open(s , fmode_read))   return FALSE;

   if(dos_getdiskfreespace(toupper(d[0])-'A'+1) < (fi.len() + copy_bufsize))
      return FALSE;

   if(!fo.open(d , fmode_create)) return FALSE;

   BYTE *buf = new BYTE[ copy_bufsize ];

   for(;;)
   {
      WORD copied = fi.read( buf, copy_bufsize );

      if(!copied) break;

      fo.write( buf , copied);

      if(copied != copy_bufsize) break;
   }

   delete [] buf;

   return TRUE;
}
*/

void
CopyFromCdRom( QLinkedList<DownloadFile> &files , QLinkedList<QString> &copied)
{
   QFileName copydir;

   while(copied.count())
   {
      copied.rewind();
      copied.remove();
   }

   if(getenv("CDTEMP") != NULL)
   {
      copydir = getenv("CDTEMP");

      if(copydir[1] != ':')
      {
         LOG("Invalid path specified in CDTEMP!");
         return;
      }

      copydir.upperCase();
   }
   else
   {
      copydir = QString(WorkPath) + "CD_TEMP";
   }

   copydir.delLast('\\');

   if(copydir.len() > 2)
      mkdir(copydir);

   copydir.appendBS();

   for( files.rewind() ; !files.eol() ; files++)
   {
      if(files.get().copy)
      {
         QFileName source,dest;

         source = files.get().name;
         source.stripPath();

         int len = LanguageStringLength(S_COPYING_FROM_CDROM((char *)source));

         io << S_COPYING_FROM_CDROM((char *)source) << '\xFF';

         dest   = copydir + source;
         source = files.get().name;

         if(!ts_CopyFile( source , dest , 16000))
         {
            LOG( "Error copying %s to %s" , (char *)source , (char *)dest);
            io << S_ERROR_COPYING_FROM_CDROM << '\n';
         }
         else
         {
            files.get().name = dest;
            copied.add(QString(dest));

            io << QString('\b',len) << QString(' ',len) << QString('\b',len);
         }
      }
   }

}

void
DeleteFilesCopiedFromCdRom(QLinkedList<QString> &copied)
{
   for( copied.rewind() ; !copied.eol() ; copied++)
   {
      ::remove(copied.get());
   }

   while(copied.count())
   {
      copied.rewind();
      copied.remove();
   }
}
