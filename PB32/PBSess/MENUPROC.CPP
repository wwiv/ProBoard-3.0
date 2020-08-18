#include "proboard.hpp"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int
ParseData(char *s,QString *param)
{
   int i;

   for(i=0;;i++)
   {
      int inquote=0;

      while(*s==' ' && *s) s++;

      if(*s=='\0') break;

      param[i].clear();

      while(*s)
      {
         if(*s==' ' && !inquote) break;

         if(*s=='\"')
         {
            inquote = !inquote;
            s++;
            continue;
         }

         param[i] << (*s++);
      }
   }

   return i;
}


bool
TpMenuItem::CheckAccess() const
{
   if(!user.CheckAccess(access.minLevel , access.flags , access.flagsNot))
      return FALSE;

   if(access.maxLevel && user.level > access.maxLevel)
      return FALSE;

   int age = -1;

   if(user.birthDate.ok())
      age = QDate(TODAY).age(user.birthDate);

   if(access.minAge || access.maxAge)
   {
      if(age < 0)
         return FALSE;

      if((access.minAge && age < access.minAge) || (access.maxAge && age > access.maxAge))
         return FALSE;
   }

//   if(access.minTimeLeft && timer.left() < access.minTimeLeft)
//      return FALSE;

//   if(access.minTimeOnline && timer.online() < access.minTimeOnline)
//      return FALSE;

   if(!access.timeFrame.enabled())
      return FALSE;

   if(access.sex)
   {
      if(!user.sex)
         return FALSE;

      if(user.sex == SEX_MALE)
      {
         if(access.sex == 2)
            return FALSE;
      }

      if(user.sex == SEX_FEMALE)
      {
         if(access.sex == 1)
            return FALSE;
      }
   }

   DWORD speed = BaudRate;

   if(speed < 1)
      speed = 38400L;

   if(access.minSpeed && speed < access.minSpeed)
      return FALSE;

   if(access.maxSpeed && speed > access.maxSpeed)
      return FALSE;

//   if(access.nodes[(node_number-1)/8] & (1 << ((node_number-1) & 7)))
//      return FALSE;

   return TRUE;
}


int
mLogoff(char * data)
{
   if(data==NULL || data[0]!='/') Cls();

   mRunPex("/I GOODBYE");
   mShowAnsiFile("GOODBYE");
   mRunPex("/I GOODBYE2");

   LOG("User logged off");
   if(BaudRate) Delay(2000);

   throw TXQuit();

   return 0;
}

int
mGotoMenu(char *data)
{
   QString param[4];
   QString newmenu;

   int n = ParseData(data,param);

   for(int i=0;i<n;i++)
   {
/*
      if(param[i][0]=='/')
      {
         switch(toupper(param[i][1]))
            {
               case 'M':
                  {
                     MsgArea ma;

                     if(param[i][3]=='+')
                     {
                        for(int i=user.msgArea+1;i<=user.msgArea+MsgArea::highAreaNum();i++)
                        {
                           int area = ((i-1)%MsgArea::highAreaNum())+1;
                           if(!ma.read(area) || !check_access(ma.readLevel,ma.readFlags,ma.readFlagsNot)) continue;
                           user.msgArea = area;
                           break;
                        }

                        break;
                     }

                     if(param[i][3]=='-')
                     {
                        for(int i=user.msgArea+MsgArea::highAreaNum()-1;i>=user.msgArea;i--)
                        {
                           int area = ((i-1)%MsgArea::highAreaNum())+1;
                           if(!ma.read(area) || !check_access(ma.readLevel,ma.readFlags,ma.readFlagsNot)) continue;
                           user.msgArea = area;
                           break;
                        }
                        break;
                     }

                     user.msgArea =atoi(&(param[i][3]));

                     break;
                  }
               case 'F':
                  {
                     FileArea fa;

                     if(param[i][3]=='+')
                     {
                        for(int i=user.fileArea+1;i<=user.fileArea+FileArea::highAreaNum();i++)
                        {
                           int area = ((i-1)%FileArea::highAreaNum())+1;
                           if(!fa.read(area) || !check_access(fa.level,fa.flags,fa.flagsNot)) continue;
                           user.fileArea = area;
                           break;
                        }

                        break;
                     }

                     if(param[i][3]=='-')
                       {
                        for(int i=user.fileArea+FileArea::highAreaNum()-1;i>=user.fileArea;i--)
                          {
                           int area = ((i-1)%FileArea::highAreaNum())+1;
                           if(!fa.read(area) || !check_access(fa.level,fa.flags,fa.flagsNot)) continue;
                           user.fileArea = area;
                           break;
                          }
                        break;
                       }

                     user.fileArea=atoi(&(param[i][3]));
                     break;
                    }
          case 'P': {
                     char s[20];

                     io << '\n' << S_ENTER_MENU_PASSWORD;
                     io.read(s,15,READMODE_PWD);
                     io << "\n\xFF";

                     if(!s[0]) return;

                     if(strcmpl(&(param[i][3]),s))
                       {
                        LOG(1,"Wrong passWORD for menu <%s> : %s",newmenu,strupr(s));
                        io << '\n' << S_ACCESS_DENIED << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
                        return;
                       }
                    }
                    break;
         }
      }
     else
*/
      newmenu = param[i];
   }

   MenuStack.CurMenu = newmenu;

   MenuStack.Changed = true;

   return 0;
}

int
mGosubMenu(char *data)
{
   MenuStack.push(MenuStack.CurMenu);

   mGotoMenu(data);

   if(!MenuStack.Changed)
      MenuStack.pop(MenuStack.CurMenu);

   return 0;
}

int
mPrevMenu(char *)
{
   MenuStack.pop(MenuStack.CurMenu);

   MenuStack.Changed = true;

   return 0;
}

int
mGotoMenuClear(char *data)
{
   MenuStack.clear();

   mGotoMenu(data);

   return 0;
}

#define MAX_ITEMS 255

void
ExecuteMenuFunction(TpMenuItem *item)
{
   if(item->attr & MENU_PASSWORD)
   {
      char s[20];

      io << '\n' << S_ENTER_SELECTION_PASSWORD;
      Input(s,15,INPUT_PWD);
      io << "\n\xFF";

      if(!s[0]) return;

      if(stricmp(item->password,s))
      {
         LOG(1,"Wrong passWORD in menu <%s>",(char *)MenuStack.CurMenu);

         io << '\n' << S_ACCESS_DENIED << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

         return;
      }
   }

   (*menufunctions[item->function])(ReplaceStringVars(item->data));
}

QString
TranslateMenuText(char *s,BYTE color,BYTE highlight,bool prompt)
{
   QString str;
   bool high = false;

   if(*s == ';')  return "";
   if(*s == '\0') return "\n";

   str << FullColorString(color);

   for(;*s;s++)
   {
      char c = *s;

      switch(c)
      {
         case '^':   high = !high;
                     if(high)
                        str << FullColorString(highlight);
                     else
                        str << FullColorString(color);
                     break;

         case '~':   str << "@<TMLEFT>@";
                     break;

         case '`':   str << "@<CURMSGAREA>@";
                     break;

         case '@':   if(*(s+1)=='<' || (*(s-1))=='>')
                        str << '@';
                     else
                        str << "@<CURFILEAREA>@";
                     break;

         case '\\':  c = *(s+1);
                     if(c>='1' && c<='7')
                     {
                        str << char(c - '0');
                        s++;
                        continue;
                     }
                     if(c=='0')
                     {
                        str << FullColorString(color);
                        s++;
                        continue;
                     }
                     c = '\\';

         default:    str << c;
      }
   }

   if(!prompt)
   {
      if(str[str.len()-1] == ';')
         str[str.len()-1] = '\0';
      else
         str << '\n';
   }

   return ReplaceStringVars(str);
}


void
MenuProcessor()
{
   int i,j;
   char hotkeys[MAX_ITEMS];
   QFile f;
   _TpMenuFile *menufile;
   TpMenuItem **items = NULL;
   int numallocated  = 0;
   int numitems      ;
   int glob_numitems = 0;

   menufile = new _TpMenuFile;

   MenuStack.CurMenu = "TOP";

   for(;;)
   {
      LOG(3,"Menu: %s",(char *)MenuStack.CurMenu);

      MenuStack.Changed = false;
      MenuStack.Update  = false;

      if(f.open(QFileName(cfg.mnuPath,"GLOBAL.PBM")))
      {
         glob_numitems = int((f.len() - sizeof(_TpMenuFile)) / sizeof(TpMenuItem));
         f.close();
      }

      if(!f.open(QFileName(cfg.mnuPath,MenuStack.CurMenu,".PBM")))
      {
         if(MenuStack.CurMenu == QString("TOP")) throw TXFatalError("NO TOP MENU");
         MenuStack.clear();
         LOG("ERROR: Menu %s not found!",(char *)MenuStack.CurMenu);
         MenuStack.CurMenu = "TOP";
         continue;
      }

      if(items    != NULL)
      {
         for(i=0;i<numallocated;i++)
            delete items[i];

         delete [] items;
      }

      numitems=int((f.len() - sizeof(_TpMenuFile)) / sizeof(TpMenuItem));

      items = new TpMenuItem *[numitems + glob_numitems];

      for(i=0;i<numitems+glob_numitems;i++)
         items[i] = new TpMenuItem;

      numallocated = i;

      f.read(menufile,sizeof(_TpMenuFile));

      for(i=0;i<numitems;i++)
         f.read(items[i],sizeof(TpMenuItem));

      f.close();

      if(f.open(QFileName(cfg.mnuPath,"GLOBAL.PBM")))
      {
         f.seek(sizeof(_TpMenuFile));

         for(i=numitems;i<numitems+glob_numitems;i++)
            f.read(items[i],sizeof(TpMenuItem));

         f.close();

         numitems += glob_numitems;
      }

      char cols[] = { 0,4,2,6,1,5,3,7 };

      for(i=0;i<numitems;i++)
      {
         if(items[i]->color & 0x8)
            items[i]->color &= 0xF7;
         else
            items[i]->color |= 0x08;

         items[i]->color = cols[items[i]->color & 7]
                          |cols[(items[i]->color&0x70) >> 4] << 4
                          |(items[i]->color & 0x8);
      }


      if(menufile->highlight & 0x8)
         menufile->highlight &= 0xF7;
      else
         menufile->highlight |= 0x08;

      menufile->highlight = cols[menufile->highlight & 7]
                           |cols[(menufile->highlight&0x70) >> 4] << 4
                           |(menufile->highlight & 0x8);



      for(i=0,j=0;i<numitems;i++)
         if(items[i]->CheckAccess())
            if(items[i]->hotKey>13 && items[i]->function)
               hotkeys[j++] = (char) toupper(items[i]->hotKey);

      hotkeys[j++]='\r';
      hotkeys[j++]=';';
      hotkeys[j]=0;

      for(;;)
      {
         char k;

      again:

         if(MenuStack.Update) break;

         //io.disablestop();
         io << "\n\f\xFF";

         for(i=0;i<numitems;i++)
         {
            if(!items[i]->CheckAccess())
               continue;

            if(items[i]->function==40)
            {
               k=SendFile(ReplaceStringVars(items[i]->data),hotkeys);

               if(k>2)
               {
                  io << " \7" << k << "\n\xFF";
                  for(int j=0;j<numitems;j++)
                     if(items[j]->hotKey==k && items[j]->CheckAccess())
                     {
                        if(items[j]->function) ExecuteMenuFunction(items[j]);
                        if(MenuStack.Changed) break;
                     }

                  if(MenuStack.Changed) break;

                  goto again;
               }
            }
            else
               if(items[i]->hotKey==1)
               {
                  ExecuteMenuFunction(items[i]);

                  if(MenuStack.Changed) break;
               }

            k = Send(TranslateMenuText(items[i]->text,
                                           items[i]->color,
                                           menufile->highlight,
                                           FALSE),hotkeys);

            if(k==1) break;

            if(k>1)
            {
               io << " \7" << k << "\n\xFF";
               for(int j=0;j<numitems;j++)
                  if(items[j]->hotKey==k && items[j]->CheckAccess())
                  {
                     if(items[j]->function) ExecuteMenuFunction(items[j]);
                     if(MenuStack.Changed) break;
                  }

               if(MenuStack.Changed) break;

               goto again;
            }
         }

         if(MenuStack.Changed) break;

         io << '\n' << TranslateMenuText(menufile->prompt,   // hidden constructor
                                          menufile->color,
                                          menufile->highlight,
                                          TRUE);

         k = WaitKeys(hotkeys);

         for(i=0;i<numitems;i++)
            if(k==items[i]->hotKey && items[i]->CheckAccess())
            {
               io << k << "\n\xFF";
               ExecuteMenuFunction(items[i]);
               if(MenuStack.Changed) break;
            }

         if(MenuStack.Changed) break;

         io << "\n\xFF";
      }
   }
}

