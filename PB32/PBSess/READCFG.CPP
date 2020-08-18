#include "proboard.hpp"

#include <string.h>



bool
TpConfig::Read()
{
   QFile f;
   QFileName fn(SysPath,"CONFIG.PB");

   if(!f.open(fn))
   {
      throw TXFatalError(form("Can't read file %s",(char *)fn));
   }
   else
   {
      if(f.len()!=sizeof(_TpConfig) || f.read(this,sizeof(_TpConfig))!=sizeof(_TpConfig))
         throw TXFatalError(form("File <%s> is invalid." , (char *)fn));
   }

   f.close();

   if(memcmp(dateStampSignature,"ecwqnoiwef",10))
   {
      memcpy(dateStampSignature,"ecwqnoiwef",10);
      dateStamp.today();
      dateStampCrc = crc32(dateStampSignature,13);

      f.open(fn,fmode_create);
      f.write(this,sizeof(_TpConfig));
      f.close();
   }

   if(dateStampCrc != crc32(dateStampSignature,13))
   {
      pastFirstUse = 61;
   }
   else
   {
      pastFirstUse = QDate(TODAY) - dateStamp;
   }

   append_backspace(txtPath);
   append_backspace(mnuPath);
   append_backspace(msgPath);
   append_backspace(uploadPath);
   append_backspace(pexPath);
   append_backspace(pvtUploadPath);
   append_backspace(nodeListDir);

   if(pwdChar == '\0') pwdChar = '#';

   if(IObuffersize < 1 || IObuffersize > 9999)
      IObuffersize = 1;

   TpUser::SetDir(msgPath);

   return TRUE;
}
