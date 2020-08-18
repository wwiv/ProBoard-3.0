#include "proboard.hpp"

#include <string.h>


long
FindTagEntry(QFile& f)
{
   char name[36];

   f.seek(0);
   for(;;)
   {
      if(f.read(name,36) != 36)
         return -1;

      long p = f.pos();

      if(name[0] && !stricmp(name,user.name))
         return p;

      WORD n;

      if(f.read(&n,sizeof(n)) != sizeof(n))
         return -1;

      f.seek(long(n) * sizeof(TpFilesIdx),seek_cur);
   }
}

void
WriteTagList()
{
   QFile f;

   if(!f.open(QFileName(SysPath,"TAGLIST.PB"),fmode_rw|fmode_copen))
      return;

   long p = FindTagEntry(f);

   if(p > 0)
   {
      f.seek(p - 36);
      f.write("",1);        // Invalidate entry
   }

   if(TagList.count())
   {
      f.seek(0,seek_end);

      f.write(user.name,36);

      WORD n = TagList.count();

      f << n;

      TagList.rewind();

      for(WORD i=0;i<n;i++,TagList++)
      {
         f.write(&TagList.get(),sizeof(TagList.get()));
      }
   }
}

void
ReadTagList()
{
   QFile f;

   TagList.kill();

   if(!f.open(QFileName(SysPath,"TAGLIST.PB"),fmode_read))
      return;

   long p = FindTagEntry(f);

   if(p < 0)
      return;

   WORD n;

   f >> n;

   for(WORD i=0;i<n;i++,TagList++)
   {
      TpFilesIdx fi;

      if(f.read(&fi,sizeof(fi)) != sizeof(fi))
         break;

      TagList.add(fi);
   }
}
