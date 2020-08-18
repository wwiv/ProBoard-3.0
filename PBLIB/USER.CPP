#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <tslib.hpp>
#include "pblib.hpp"

QString _TpUser::sysDir;
QString _TpUser::lastSearchSpec;

bool   _TpUser::lastSearchAlias;
bool   _TpUser::lastSearchExact;
bool   _TpUser::lastSearchFuzzy;

long   _TpUser::lastSearchRecord = -1;

_TpUser::_TpUser()
{
   CLEAR_OBJECT( *this );
}

bool
_TpUser::Read( long rec )
{
   QFileName fn(sysDir , "USERS.PB");
   QFile     f;

   if(!f.open(fn))
   {
      return false;
   }

   f.seek(rec * sizeof(*this));
   f.read(this,sizeof(*this));

   strip_all(alias);

   if(alias[0] == '\0')
      strcpy(alias,name);

   if(screenLength < 5)
      screenLength = 24;

   return true;
}

long
_TpUser::NumUsers()
{
   QFileName fn(sysDir , "USERS.PB");

   QFile     f;

   if(!f.open(fn))
   {
      return 0;
   }

   return f.len() / sizeof(_TpUser);
}


bool
_TpUser::Write( bool append )
{
   if(!strcmp(alias,name))
      alias[0] = '\0';

   if(append)
      record = NumUsers();

   QFileName fn(sysDir , "USERS.PB");
   QFile     f;

   if(!f.open(fn,fmode_write|fmode_copen))
      return false;

   f.seek(record * sizeof(*this));
   f.write(this,sizeof(*this));
   f.close();

   fn(sysDir , "USERSIDX.PB");

   if(!f.open(fn,fmode_write|fmode_copen))
      return false;

   _TpUserIdx uidx;

   uidx.nameCrc = crc32(name);
   uidx.aliasCrc = crc32(alias);

   f.seek(record * sizeof(uidx));
   f.write(&uidx,sizeof(uidx));
   f.close();


   return true;
}

bool
_TpUser::Search()
{
   DWORD crc = crc32(lastSearchSpec);

   QFile  f;

   bool found = false;

   _TpUser *u       = new _TpUser;
   _TpUserIdx *uidx = new _TpUserIdx;

   if(lastSearchExact)
   {
      if(f.open(QFileName( sysDir , "USERSIDX.PB" ), fmode_read , 2048))
      {
         f.seek((++lastSearchRecord) * sizeof(*uidx));

         for(;;)
         {
            if(f.read( uidx , sizeof(*uidx) ) != sizeof(*uidx)) break;

            if(lastSearchAlias)
            {
               if(crc == uidx->aliasCrc)
               {
                  found = true;
                  break;
               }
            }
            else
            {
               if(crc == uidx->nameCrc)
               {
                  found = true;
                  break;
               }
            }

            lastSearchRecord++;
         }

         if(!found)
            lastSearchRecord = f.len() / sizeof(*u);
      }
   }
   else
   {
      if(f.open(QFileName( sysDir , "USERS.PB" ), fmode_read , 4096))
      {
         f.seek((++lastSearchRecord) * sizeof(*u));

         for(;;)
         {
            if(f.read( u , sizeof(*u) ) != sizeof(*u)) break;

            QString sName(u->name);
            QString sHandle(u->alias);

            if(lastSearchAlias)
            {
               if(lastSearchFuzzy)
               {
                  if(sHandle.fuzzySearch(lastSearchSpec,75) > 0)
                  {
                     found = true;
                     break;
                  }
               }
               else
               {
                  if(!stricmp( u->alias , lastSearchSpec))
                  {
                     found = true;
                     break;
                  }
               }
            }
            else
            {
               if(lastSearchFuzzy)
               {
                  if(sName.fuzzySearch(lastSearchSpec,75) > 0)
                  {
                     found = true;
                     break;
                  }
               }
               else
               {
                  if(!stricmp( u->name , lastSearchSpec))
                  {
                     found = true;
                     break;
                  }
               }
            }

            lastSearchRecord++;
         }

         if(!found)
            lastSearchRecord = f.len() / sizeof(*u);
      }
   }

   f.close();

   delete u;
   delete uidx;

   if(found)
   {
      Read(lastSearchRecord);
   }

   return found;
}

bool
_TpUser::Search( char *spec , bool exact , bool fuzzy , bool findalias )
{
   lastSearchSpec   = spec;
   lastSearchExact  = exact;
   lastSearchFuzzy  = fuzzy;
   lastSearchAlias  = findalias;
   lastSearchRecord = -1;

   return Search();
}

bool
_TpUser::SearchNext()
{
   return Search();
}

void
_TpUser::NewUser()
{
   CLEAR_OBJECT(*this);

   defaultProtocol = 'Z';

   strcpy(language, "ENGLISH");

   screenWidth       = 80;
   screenLength      = 24;
   logLevel          = 1;
   //uFlags            = UFLAG_HOTKEYS;
   qwkMaxMsgsPerArea = 100;
   qwkMaxMsgs        = 500;
   fileArea          = 1;
   msgArea           = 1;

   memset(&mailCheckBoards,0xFF,125);
   memset(&combinedBoards ,0xFF,125);
}

QString
_TpUser::FirstName()
{
   char s[36];

   strcpy(s,name);

   if(strchr(s,' '))
      *strchr(s,' ') = '\0';

   return QString(s);
}

bool
_TpUser::CheckAccess(WORD lv,TpAccessFlags fl)
{
    if(level < lv)
      return false;

    for(int i=1;i<=32;i++)
      if(fl.getflag(i))
         if(!aFlags.getflag(i))
            return false;

    return true;
}

bool
_TpUser::CheckAccess(WORD lv,TpAccessFlags fl,TpAccessFlags notfl)
{
    if(level<lv)
      return false;

    for(int i=1;i<=32;i++)
      if(fl.getflag(i))
         if(!aFlags.getflag(i))
            return false;

    for(i=1;i<=32;i++)
      if(notfl.getflag(i))
         if(aFlags.getflag(i) )
            return false;

    return true;
}
