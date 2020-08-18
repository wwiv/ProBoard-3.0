#include "proboard.hpp"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

QFile TpFileArea::f;
int  TpFileArea::lastAreaNum = -1;
int  TpFileArea::numAreas = -1;

TpFileArea *TpFileArea::lastArea = NULL;

void
TpFileArea::open()
{
   if(!f.opened())
   {
      if(!f.open(QFileName(SysPath,"FILECFG.PRO"),fmode_read,4096))
         throw TXFileError("FILECFG.PRO");

      numAreas = int(f.len() / sizeof(_TpFileArea));
   }
}

bool
TpFileArea::read(int a)
{
   open();

   if(a<1 || a>numAreas) return FALSE;

   if(lastArea == NULL)
   {
      lastArea = new TpFileArea;
      lastAreaNum = -1;
   }

   if(a != lastAreaNum)
   {
      f.seek(long(a-1) * sizeof(_TpFileArea));

      if(   f.read(lastArea,sizeof(_TpFileArea)) != sizeof(_TpFileArea)
         || lastArea->name[0] == '\0' )
      {
         lastAreaNum = -1;

         return FALSE;
      }
   }

   (*this) = (*lastArea);


   append_backspace(filePath);

   strip_trailing( listPath );
   strip_leading( listPath );

   if(listPath[0] == '\0')
   {
      strcpy(listPath , filePath);
      strcat(listPath , "FILES.BBS");
   }

   lastAreaNum = a;

   areaNum = a;

   strip_trailing( name );
   strip_leading( name );

   return (name[0]) ? TRUE:FALSE;
}

void
TpFileArea::close()
{
    f.close();

    if(lastArea != NULL) delete lastArea;

    lastAreaNum = -1;
    numAreas    = -1;
    lastArea    = NULL;
}

int
TpFileArea::highAreaNum()
{
    open();

    return numAreas;
}

void
CreateAreaList(QString param[],int numpara,QBitArray& arealist,bool msgareas)
{
   TpFileArea fa;
   TpMsgArea ma;
   int MAX;

   if(msgareas)
      MAX = TpMsgArea::highAreaNum();
   else
      MAX = TpFileArea::highAreaNum();

   for(int i=0;i<numpara;i++)
   {
      char *ptr=param[i];
      int incl=1,offset=0;
      int kindfilter = 0;

      if(ptr[0]=='/') continue;

      if(ptr[0]=='-') { incl=0; offset=1; }
      if(ptr[0]=='+') { incl=1; offset=1; }

      switch(toupper(ptr[offset]))
      {
         case 'E': kindfilter = MSG_ECHO;   break;
         case 'N': kindfilter = MSG_NET;    break;
         case 'L': kindfilter = MSG_LOCAL;  break;
      }

      switch(toupper(ptr[offset]))
      {
         case '*':
            {
               for(int j=1;j<=MAX;j++)
                  if(incl)
                     arealist.set(j);
                  else
                     arealist.clear(j);
            }
            break;

         case 'C':
            {
               if(msgareas) break;

               for(int j=1;j<=MAX;j++)
               {
                  if(fa.read(j))
                     if(fa.cdrom)
                        if(incl)
                           arealist.set(j);
                        else
                           arealist.clear(j);
               }
            }
            break;

         case 'X':
            {
               if(msgareas)
               {
                  if(incl)
                     arealist.set(user.msgArea);
                  else
                     arealist.clear(user.msgArea);
               }
               else
               {
                  if(incl)
                     arealist.set(user.fileArea);
                  else
                     arealist.clear(user.fileArea);
               }
            }
            break;

         case 'N':
         case 'L':
         case 'E':
            {
               if(!msgareas) break;

               for(int j=1;j<=MAX;j++)
               {
                  if(ma.read(j))
                     if(ma.msgKind == kindfilter)
                        if(incl)
                           arealist.set(j);
                        else
                           arealist.clear(j);
               }
            }
            break;

         default:
            {
               if(strchr(ptr+offset,'-'))
               {
                  int from = atoi(strtok(ptr+offset,"-"));
                  int to   = atoi(strtok(NULL,"-"));

                  for(int j=from;j<=to;j++)
                  {
                     if(incl)
                        arealist.set(j);
                     else
                        arealist.clear(j);
                  }
               }
               else
               {
                  int j = atoi(ptr+offset);

                  if(incl)
                     arealist.set(j);
                  else
                     arealist.clear(j);
               }
            }
            break;
      }
   }
}
