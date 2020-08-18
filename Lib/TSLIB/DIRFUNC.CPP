/***************************************************************************
 Directory functions

 Compatibility: DOS, OS/2, Windows
 Models       : 16 bit - 32 bit
***************************************************************************/

#ifdef PEX
   #include <pb_sdk.h>
#else
   #include <io.h>
   #include <string.h>
   #include <ctype.h>
   #include <direct.h>
#if defined(_WIN32)
   #include <windows.h>
#elif defined(__WATCOMC__)
   #include <dos.h>
#endif
#endif

#include "tslib.hpp"

static char *
ts_DelLastChar( char *text, char chr )
{
   int len = strlen (text) - 1;

   if(text[len] == chr)
      text[len] = '\0';

   return text;
}


bool
ts_MakeFullDir(char *path)
{
   char str[128];

   str[0] = '\0';

   strcpy(str,path);

   char *p = strrchr(str,':');

   if(p)
   {
      *(p+1) = '\0';

      p = strrchr(path,':') + 1;
   }
   else
   {
      str[0] = '\0';

      p = path;
   }

   /* Vanaf hier wijst p naar de pathname zonder drive, en str[] bevat */
   /* de drive (als er een is)                                         */

   if(*p == '\\')
   {
      str[strlen(str)+1] = '\0';
      str[strlen(str)]   = *p++;
   }

   for(;;p++)
   {
      if(*p == '\\' || *p == '\0')
      {
         ts_DelLastChar(str,'\\');

         if(!ts_DirExists(str))
            if(mkdir(str) < 0)
               return false;
      }

      str[strlen(str)+1] = '\0';
      str[strlen(str)  ] = *p;

      if(*p == '\0') break;
   }

   return TRUE;
}

bool
ts_DirExists(char *path)
{
   QString s(path);

   s.delLast('\\');

   if(s[1]==':' && s.len() <= 2)
      return true;

   QDirScan scan(s,DIR_DIREC);

   return bool(int(scan) && (scan.flags() & DIR_DIREC));
}

QString
ts_ResolveDir(char *dir)
{
   char cur_drive,drive;
   char cur_dir[256];
   QFileName tmp_dir;

   cur_drive = drive = char(_getdrive()-1);

#ifdef __WATCOMC__
   getcwd(cur_dir,255);
#else
   _getdcwd(cur_drive+1,cur_dir,255);
#endif

   if(strchr(dir,':'))
   {
      if(dir[1] != ':')
         return "";

      drive = char(toupper(dir[0]) - 'A');

#ifdef __WATCOMC__
      getcwd(cur_dir,255);
#else
      _getdcwd(drive+1,cur_dir,255);
#endif

      tmp_dir = &dir[2];
   }
   else
   {
      tmp_dir = dir;
   }

   if(tmp_dir[0] != '\\')
   {
      tmp_dir.insert(0,"\\");
      tmp_dir.insert(0,cur_dir);
      tmp_dir.insert(0,"\\");
   }

   tmp_dir.appendBS();           // tmp_dir contains full directory

   QString dir_stack[30];
   int stack_p = 0;

   char *s = strtok(tmp_dir,"\\");

   while(s)
   {
      QString tmp = s;

      if(tmp == (char *)"..")
      {
         if(stack_p)
            stack_p--;
      }
      else
      {
         if(tmp != (char *)".")
            dir_stack[stack_p++] = tmp;
      }

      s = strtok(NULL,"\\");
   }

   tmp_dir = char(drive+'A');

   tmp_dir << ":\\";

   for(int i=0;i<stack_p;i++)
   {
      tmp_dir << dir_stack[i] << '\\';
   }

   return tmp_dir;
}


bool
ts_IsFullPath(char *s)
{
   if(strlen(s) < 3 || strncmp(&s[1],":\\",2))
      return false;

   return bool(!!isalpha(s[0]));
}

void
ts_MakeInputPath(QString& s)
{
   s.delLast('\\');
   if(s.lastChar() == ':')
      s << '\\';
}

void
ts_MakeInputPath(char *s)
{
   if(strlen(s) >= 3)
   {
      ts_DelLastChar(s,'\\');

      if(s[strlen(s)-1] == ':')
         strcat(s,"\\");
   }
}

bool
ts_SyncFileDate(char *fn1,char *fn2)
{
   QFile f1,f2;

   if(!f1.open(fn1) || !f2.open(fn2,fmode_rw))
      return false;

   FILETIME tm1,tm2,tm3;

   if(GetFileTime(fn1,&tm1,&tm2,&tm3))
   {
	  if(SetFileTime(fn2,&tm1,&tm2,&tm3))
		  return true;
	 }

   return false;
}

long
ts_DiskFreeSpace(char *dir)
{
   long ret = 0;

#ifdef _WIN32
   DWORD n1,n2,n3,n4;

   if(dir[1] != ':')
   {
      BOOL r = GetDiskFreeSpace(NULL,&n1,&n2,&n3,&n4);

      if(r)
         ret = n1*n2*n3;
   }
   else
   {
      char *s = new char[strlen(dir)+1];

      strcpy(s,dir);
      if(strchr(s,'\\'))
         *(strchr(s,'\\')+1) = '\0';

      BOOL r = GetDiskFreeSpace(s,&n1,&n2,&n3,&n4);

      if(r)
         ret = n1*n2*n3;

      delete [] s;
   }
#endif

   return ret;
}
