#include "proboard.hpp"

#include <string.h>

TpMsgBase *
TpMsgArea::MsgBase()
{
   switch(msgBaseType)
   {
      case MSGBASE_SDM   :
//      case MSGBASE_SQUISH: return node->squishMsgBase;
      case MSGBASE_JAM   : return jamMsgBase;
      case MSGBASE_HUDSON: return hudsonMsgBase;
      default            : throw TXFatalError("Bad message base type");
                           return NULL;
   }
}


void
TpMsgArea::open()
{
    if(!f.opened())
    {
       if(!f.open(QFileName(SysPath,"MSGAREAS.PB"),fmode_read,8192))
         throw TXFatalError("MSGAREA - Unable to open MSGAREAS.PB");

       numAreas = int(f.len() / sizeof(_TpMsgArea));
    }
}

bool
TpMsgArea::read(int a)
{
   open();

   if(a<1 || a>numAreas) return FALSE;

   f.seek(long(a-1) * sizeof(_TpMsgArea));

   if(   f.read(this,sizeof(_TpMsgArea)) != sizeof(_TpMsgArea)
      || name[0] == '\0' )
   {
      return FALSE;
   }

   if(msgBaseType != MSGBASE_HUDSON)
   {
      append_backspace(path);

      if(msgBaseType !=  MSGBASE_SDM) path[strlen(path)-1] = '\0';
   }

   if(!sysop[0]) strcpy(sysop,cfg.sysopName);

   if(!replyBoard) replyBoard = areaNum;

   strip_trailing( name );
   strip_leading( name );

   return (name[0]) ? true:false;
}

void
TpMsgArea::close()
{
    f.close();
}

int
TpMsgArea::highAreaNum()
{
   QFile f;

   if(!f.open(QFileName(SysPath,"MSGAREAS.PB"),fmode_read,8192))
      throw TXFatalError("MSGAREA - Unable to open MSGAREAS.PB");

   return int(f.len() / sizeof(_TpMsgArea));
}

bool
TpMsgArea::sysopAccess()
{
    return (    user.CheckAccess(sysopLevel,sysopFlags,sysopFlagsNot)
            || !strcmpl(sysop,user.name)
            || !strcmpl(cfg.sysopName,user.name)
           );
}

