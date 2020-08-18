#include "proboard.hpp"

#include <string.h>
#include <stdlib.h>

int
mSelectMessageArea(char *data)
{
   TpMsgArea ma;
   int areanum = 0;
   QString param[50];
   WORD group = 0;
   bool group_specified = FALSE;
   bool listareas = FALSE;
   bool show_lastread = TRUE;
   bool list_specified = FALSE;

   QBitArray arealist(10000,1);

   int npara = ParseData(data,param);

   for(int i=0;i<npara;i++)
   {
      param[i].upperCase();

      if(param[i] == QString("/L"))
         listareas     = TRUE;

      if(param[i] == QString("/N"))
         show_lastread = FALSE;

      if(param[i] == QString("/MG"))
      {
         group           = user.msgGroup;
         group_specified = TRUE;
      }

      if(!strnicmp(param[i],"/MG=",4))
      {
         group           = atoi(&param[i][4]);
         group_specified = TRUE;
      }

      if(param[i][0] != '/') list_specified = TRUE;
   }

   if(list_specified)
   {
      CreateAreaList(param,npara,arealist,TRUE);
   }
   else
   {
      for(i = 1 ; i <= 10000 ; i++)
         arealist.set(i);
   }

   if(group_specified && group == 0)
   {
      mSelectMsgAreaGroup("");

      group = user.msgGroup;

      if(!group)
         return 1;

      io << '\n';
   }

   for(bool shown=FALSE;;shown=TRUE)
   {
      if(!listareas)
      {
         io << '\n' << S_ENTER_MESSAGE_AREA_NUMBER;
         if(!shown) io << S_PRESS_ENTER_TO_LIST;
         io << ": ";
         if(Input(areanum,5)>=0) break;

         if(shown) return 1;

         io << "\n\f\n" << S_SELECT_MESSAGE_AREA_TITLE << "\n\n";

         LineCounter(3);
      }

      EnableStop();

      for(int i=1,count=0;i<=TpMsgArea::highAreaNum();i++)
      {
         QString newmail = " ";

         if(!arealist[i] || !ma.read(i) || !user.CheckAccess(ma.readLevel,ma.readFlags,ma.readFlagsNot)) continue;

         if(group && !ma.allGroups)
         {
            for(int g=0;g<4;g++)
            {
               if(ma.groups[g] == group)
                  break;
            }

            if(g==4)
               continue;
         }

         if(!listareas && show_lastread)
            if(ma.lastRead() < ma.highMsg())
               newmail = "\7*";

         io << form("\3%4d. %s \6%-30.30s ",i,(char *)newmail,ma.name);

         if(OutputStopped) break;

         if(!((++count)%2))
         {
            io << '\n';
            if(LineCounter()) break;
         }
      }

      if(count%2) io << '\n';

      if(listareas) break;
   }

   if(!listareas)
   {
      io << '\n';

      if(!arealist[areanum] || !ma.read(areanum) || (!user.CheckAccess(ma.readLevel,ma.readFlags,ma.readFlagsNot) && !ma.sysopAccess()))
      {
         io << '\n' << S_UNKNOWN_MESSAGE_AREA << ' ' << S_PRESS_ENTER_TO_CONTINUE;
         return 0;
      }

      user.msgArea = areanum;

      MenuStack.Update = TRUE;
   }

   return 0;
}

int
mSelectFileArea(char *data)
{
   TpFileArea fa;
   WORD group = 0;
   int areanum = 0;
   bool arealist_created = FALSE;
   bool group_specified = FALSE;
   QString param[50];
   QBitArray arealist(10000 , 1);

   int npara = ParseData(data,param);

   for(int i=0;i<npara;i++)
  {
   param[i].upperCase();

   if(param[i] == QString("/FG"))
   {
      group         = user.fileGroup;
      group_specified = TRUE;
   }
   if(!strnicmp(param[i],"/FG=",4))
   {
      group = atoi(&param[i][4]);
      group_specified = TRUE;
   }
  }


if(group_specified && group == 0)
{
   mSelectFileGroup("");

   group = user.fileGroup;

   if(!group)
      return 1;

   io << '\n';
}

for(bool shown=FALSE;;shown=TRUE)
  {
   io << '\n' << S_ENTER_FILE_AREA_NUMBER;
   if(!shown) io << S_PRESS_ENTER_TO_LIST;
   io << ": ";
   if(Input(areanum,4)>=0) break;

   if(shown) return 1;

   io << "\f\n" << S_SELECT_FILE_AREA_TITLE << "\n\n";

   io << "\x17.";

   CreateAreaList(param,npara,arealist);
   arealist_created = TRUE;

   io << '\r';

   LineCounter(3);
   EnableStop();

   for(int i=1,count=0;i<=TpFileArea::highAreaNum();i++)
     {
      if(!arealist[i] || !fa.read(i)) continue;

      if(!user.CheckAccess(fa.level,fa.flags,fa.flagsNot)) continue;

      if(group && !fa.allGroups)
      {
         for(int g=0;g<4;g++)
         {
            if(fa.groups[g] == group)
               break;
         }

         if(g==4)
            continue;
      }

      io << form("\3%4d. \6%-29.29s ",i,fa.name);

      if(OutputStopped) break;
      if((count++)%2)
        {
         io <<'\n';
         if(LineCounter()) break;
        }
     }

   if(count%2) io << '\n';
  }

io << '\n';

if((arealist_created && !arealist[areanum]) || !fa.read(areanum) || !user.CheckAccess(fa.level,fa.flags,fa.flagsNot))
  {
   io << '\n' << S_UNKNOWN_FILE_AREA << ' ' << S_PRESS_ENTER_TO_CONTINUE;
   return 0;
  }

user.fileArea = areanum;

   MenuStack.Update = TRUE;

   return 0;
}

int
mSelectFileGroup(char *)
{
   QFile f;
   _TpAreaGroup group;

   f.open(QFileName(SysPath,"FGROUPS.PB"));

   io << "\f\n" << S_SELECT_FILE_AREA_GROUP_TITLE << "\n\n";

   LineCounter(3);
   EnableStop();

   for(int i=1,count=0;;i++)
   {
      if(f.read(&group,sizeof(group)) != sizeof(group))
         break;

      if(!user.CheckAccess(group.level,group.flags,group.flagsNot))
         continue;

      if(!group.name[0])
         continue;

      io << form(" \3%3d. \6%-29.29s ",i,group.name);

      if(OutputStopped) break;

      if((count++)%2)
      {
         io <<'\n';
         if(LineCounter()) break;
      }
   }

   if(count%2) io << '\n';

   int groupnum = 0;

   io << '\n' << S_ENTER_GROUP_NUMBER;

   if(Input(groupnum,3) < 0) return 1;

   io << '\n';

   if(groupnum < 1 || groupnum > 255)
      io << '\n' << S_UNKNOWN_GROUP << ' ' << S_PRESS_ENTER_TO_CONTINUE;

   f.seek(long(groupnum-1) * sizeof(group));

   if(f.read(&group,sizeof(group)) != sizeof(group) || !user.CheckAccess(group.level,group.flags,group.flagsNot))
      io << '\n' << S_UNKNOWN_GROUP << ' ' << S_PRESS_ENTER_TO_CONTINUE;

   user.fileGroup = groupnum;

   MenuStack.Update = TRUE;

   return 0;
}

int
mSelectMsgAreaGroup(char *)
{
   QFile f;
   _TpAreaGroup group;

   f.open(QFileName(SysPath,"MGROUPS.PB"));

   io << "\f\n" << S_SELECT_MSG_AREA_GROUP_TITLE << "\n\n";

   LineCounter(3);
   EnableStop();

   for(int i=1,count=0;;i++)
   {
      if(f.read(&group,sizeof(group)) != sizeof(group))
         break;

      if(!user.CheckAccess(group.level,group.flags,group.flagsNot))
         continue;

      if(!group.name[0])
         continue;

      io << form(" \3%3d. \6%-29.29s ",i,group.name);

      if(OutputStopped) break;

      if((count++)%2)
      {
         io <<'\n';
         if(LineCounter()) break;
      }
   }

   if(count%2) io << '\n';

   int groupnum = 0;

   io << '\n' << S_ENTER_GROUP_NUMBER;

   if(Input(groupnum,3) < 0) return 1;

   io << '\n';

   if(groupnum < 1 || groupnum > 255)
   {
      io << '\n' << S_UNKNOWN_GROUP << ' ' << S_PRESS_ENTER_TO_CONTINUE;
      return 1;
   }

   f.seek(long(groupnum-1) * sizeof(group));

   if(f.read(&group,sizeof(group)) != sizeof(group) || !user.CheckAccess(group.level,group.flags,group.flagsNot))
   {
      io << '\n' << S_UNKNOWN_GROUP << ' ' << S_PRESS_ENTER_TO_CONTINUE;
      return 1;
   }

   user.msgGroup = groupnum;

   MenuStack.Update = TRUE;

   return 0;
}


