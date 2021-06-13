#include "proboard.hpp"
#include <ctype.h>
#include <string.h>

bool
SelectProtocol(TpProtocol& p , char protocol_key , bool seldef)
{
   QString hotkeys;
   QString s;

   if(protocol_key == '\0')
   {
      s << S_PROTOCOL_MENU_TITLE << "\n\n";

      for(int i=1 ; p.Read(i) ; i++)
      {
         if(p.Flags&PROT_ENABLED && !(BaudRate>0 && (p.Flags&PROT_LOCAL)))
         {
            s << form("\6<\3%c\6>\7 %s\n",p.Key,p.Name);

            hotkeys << p.Key;
         }
         else
         {
            hotkeys << '-';
         }
      }

      s << "\n\6<\3-\6> " << (seldef ? S_NO_DEFAULT_PROTOCOL : S_PROTOCOL_MENU_GOBACK)
        << "\n\n"
        << S_PROTOCOL_MENU_PROMPT;

      hotkeys << '-';

      char k = Send(s,hotkeys);

      if(k==1) return FALSE;

      if(!k) k=WaitKeys(hotkeys);

      if(k=='-')
         return FALSE;

      for(int i=0;i<hotkeys.len();i++)
         if(k==hotkeys[i])
         {
            p.Read(i+1);
            break;
         }

      io << "\6" << p.Name << '\n';

      return TRUE;
   }
   else
   {
      for(int i=1 ; p.Read(i) ; i++)
         if(toupper(p.Key) == toupper(protocol_key))
            return TRUE;

      return FALSE;
   }
}

void
mChangeDefaultProtocol(char *)
{
   TpProtocol p;

   if(user.defaultProtocol == '\0' || !SelectProtocol(p,user.defaultProtocol))
      strcpy(p.Name,S_NO_DEFAULT_PROTOCOL);

   io << "\n\f\n" << S_CHANGE_PROTOCOL_TITLE(p.Name) << "\n\n";

   if(SelectProtocol(p,0,TRUE))
      user.defaultProtocol = p.Key;
   else
      user.defaultProtocol = 0;
}

bool
TpProtocol::Read(int n)
{
   QFile f;

   if(!f.open(QFileName(SysPath,"PROTOCOL.PB"))) return FALSE;

   f.seek(long(n-1)*sizeof(TpProtocol));

   if(f.read(this,sizeof(TpProtocol))!=sizeof(TpProtocol)) return FALSE;

   return TRUE;
}
