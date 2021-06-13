#include "proboard.hpp"

#include <string.h>

#include <ctype.h>
#include <stdlib.h>


int
Login()   // 0 -> ok   -1 -> User violation
{
   char username[36];
   char password[16];
   int i;
   bool systempwd_ok    = FALSE;
   bool login_pex_found = FALSE;

   for(;;)
   {
      user.NewUser();
      strcpy(user.language,cfg.defaultLanguage);
      user.logLevel=1;

//      if(!registered)
//      {
//         char *s = "\rProBoard v" VERSION " [UNREGISTERED]\n";
//
//         //LOG("crc = %08lX",crc32(s));
//
//         if(crc32(s) != 0xE590663CL) throw TXQuit();
//
//         io << s;
//      }

      if(cfg.useSystemPassword && cfg.systemPassword[0] && !systempwd_ok)
      {
         mShowAnsiFile("BEFOREPW");

         for(int i=0 ; i < cfg.maxPasswordInput ; i++)
         {
            char pwd[16];

            io << S_ENTER_SYSTEM_PASSWORD;

            Input(pwd,15,INPUT_PWD);

            io << "\n\n\xFF";

            if(pwd[0])
            {
               if(!stricmp(pwd,cfg.systemPassword)) break;

               io << S_WRONG_PASSWORD << "\n\n";

               LOG("Wrong system passWORD: '%s'",pwd);
            }
         }

         if(i==cfg.maxPasswordInput)
         {
            LOG("Exceeded maximum retries.");

            io << "\n\n" << S_HANGING_UP << "\n\xFF";

            LOG("Hanging up");

            ::Delay(2000);

            throw TXQuit();
         }

         systempwd_ok = TRUE;

         mShowAnsiFile("AFTERPW");
      }

      user.record = -1;

      if(mRunPex(form("/I _LOGIN %lu",(DWORD)username)) >= 0)
         login_pex_found = TRUE;

      if(user.record >= 0)
         break;

      if(!login_pex_found)
      {
         io << '\r' << S_ENTER_YOUR_NAME;

         Input(username,35,INPUT_UPFIRST);

         if(strchr(username,';')) *strchr(username,';') = '\0';

         for(i=0;username[i];i++)
            if(username[i] == '\xFF')
               username[i] = ' ';

         strip_trailing(username);
         strip_leading(username);

         if(!username[0])
         {
            if(!BaudRate)
            {
               strcpy(username,cfg.sysopName);

               io << username;

               for(i=0;i<35-(int)strlen(username);i++) io << ' ';
            }
            else
            {
               io << "\n\n\xFF";
               continue;
            }
         }

         if(CheckTrashCan(username))
         {
            LOG("Trashcan name: \"%s\"",username);
            io << "\n\n";
            if(ShowAnsiFile("TRASHCAN",NULL) == SENDFILE_NOTFOUND)
               io << S_ILLEGAL_NAME << "\n\n";
            continue;
         }


         io << "\n\n\7" << S_SCANNING_USER_FILE << char(0xFF);

         bool found = user.Search(username);

         while(found && (user.uFlags & UFLAG_DELETED))
         {
            found = user.SearchNext();
         }

         if(!found) user.record = -1;

         if(!found && cfg.allowAlias)
         {
            found = user.Search(username,TRUE,FALSE,TRUE);

            if(!found) user.record = -1;
         }

         if(user.record<0 && !cfg.allowOneWordNames && !strchr(username,' '))
         {
            LOG("Illegal name: \"%s\"",username);

            io << "\n\n" << S_WRONG_NAME_FORMAT << "\n\n";

            continue;
         }
      }

      LoginDate.today();
      LoginTime.now();

      if(user.record<0)
      {
         LOG("User not located : %s",username);

         mRunPex("/I NEWUSER");
         mShowAnsiFile("NEWUSER");

         io << "\n\n" << S_ARE_YOU_A_NEW_USER(username);

         if(Ask(0))
         {
            user.record = NewUser(username) ? int(user.record) : (-1);

            return 0;
         }
         else
         {
            io << "\n\n";
            LOG("Name misspelled (%s).",username);
            continue;
         }
      }
      else
      {
         break;
      }
   }

   ReadTagList();

   LoginDate.today();
   LoginTime.now();

   if(user.language[0])
   {
      if(!ReadLanguage(user.language))
         if(!ReadLanguage(cfg.defaultLanguage))
            throw TXFatalError("Default language not found");
   }

   if(!user.lastNewFilesCheck.ok())
      user.lastNewFilesCheck.today();

   if(user.lastDate != QDate(TODAY) || (user.uFlags & UFLAG_GUEST))
      user.timeUsed = user.kbToday = 0;

/*
   if(user.level<min_level)
   {
      LOG("User \"%s\" not allowed to logon",user.name);

      if(mShowAnsiFile("NOACCESS") == SENDFILE_NOTFOUND)
         io << "\7\n\n" << S_NO_ACCESS_ON_THIS_NODE << "\n\xFF";

      Delay(2000);

      throw TXQuit();
   }
*/

   if((user.uFlags & UFLAG_LOCALONLY) && BaudRate)
   {
      LOG("User \"%s\" not allowed to logon from remote",user.name);

      io << "\7\n\n" << S_NO_ACCESS_ON_THIS_NODE << "\n\xFF";

      Delay(2000);

      throw TXQuit();
   }

   LOG("User logged in: %s",user.name);

   if(!login_pex_found)
   {
      for(i=0;BaudRate || !cfg.allowQuickLogin;i++)
      {
         io << "\n\n";

         if(!i)
            mShowAnsiFile("BEFOREPW");

         io << S_ENTER_PASSWORD;

         Input(password,15,INPUT_PWD);

         if(user.passWord[0] == '\0')
         {
            //x if(RaCrc(password) == user.passWordCRC)
               break;
         }
         else
         {
            if(!stricmp(user.passWord,password))
               break;
         }

         LOG("Wrong passWORD: %s",password);

         io << "\n\n" << S_WRONG_PASSWORD;

         if(i==cfg.maxPasswordInput-1)
         {
            LOG("User exceeded maximum password tries");

            if(cfg.pwdMessages && !(user.uFlags & UFLAG_GUEST))
            {
               LOG("Posting message to user & sysop");
               WriteMSGTMP(form("Someone failed to login using your name on %d %s 19%d , at %02d:%02d\r\n",(char *)LoginDate.format("DD MMM YYYY"),(char *)LoginTime.format("HH:MM")));
               PostMessage("ProBoard Security Manager",user.name,"PassWORD violation",cfg.securityBoard,TRUE);

               WriteMSGTMP(form("Someone failed to login as '%s' on %d %s 19%d , at %02d:%02d\r\n",user.name,(char *)LoginDate.format("DD MMM YYYY"),(char *)LoginTime.format("HH:MM")));
               PostMessage("ProBoard Security Manager",cfg.sysopName,"PassWORD violation",cfg.securityBoard,TRUE);
            }

            io << "\n\n" << S_LEAVE_MESSAGE_TO_SYSOP;

            if(Ask(1))
            {
               io << '\n';
               mWriteMsg(form("%d /T=Sysop",cfg.securityBoard));
            }

            io << "\n\n" << S_HANGING_UP << "\n\xFF";

            LOG("Hanging up");

            Delay(2000);

            user.record = -1;

            return -1;
         }
      }

   mShowAnsiFile("AFTERPW");
   }

   io << '\n';

     if(cfg.askSex && !user.sex)
     {
         io << '\n' << S_ASK_SEX;

         char k = WaitLanguageHotkeys(K_ASK_SEX,FALSE);

         user.sex = k+1;

         io << (k ? S_FEMALE:S_MALE);

         io << '\n';
     }

     if(cfg.askBirthDay==1 && !user.birthDate.ok())
     {
         do
         {
            io << '\n' << S_ASK_BIRTHDATE(DateFormats[user.dateFormat]);

            InputDate(user.birthDate);
         }
         while(!user.birthDate.ok());

         io << '\n';
     }

   PasswordOk = TRUE;

   if(!cfg.allowAnsi) user.uFlags &= ~UFLAG_ANSI;

   if(user.expDate[0])
   {
      int ex=user.expDate-QDate(TODAY);

      if(ex<=0)
      {
         if(user.expLevel<user.level)
         {
            WORD oldlevel = user.level;
            user.level   = user.expLevel;
            int f;
            for(f=1;f<=32;f++)
               if(user.expFlagsOn.getflag(f))
                  user.aFlags.setflag(f);

            for(f=1;f<=32;f++)
               if(user.expFlagsOff.getflag(f))
                  user.aFlags.clearflag(f);

            mRunPex(form("/I EXPIRED %u",oldlevel));

            if(mShowAnsiFile("EXPIRED")==SENDFILE_NOTFOUND)
               io << '\n' << S_LEVEL_EXPIRED << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
         }
      }
      else
      {
         if(ex <= 30)
         {
            if(mShowAnsiFile("EXP_WARN")==SENDFILE_NOTFOUND)
            {
               io << '\n' << S_LEVEL_WILL_EXPIRE(form("%d",ex)) << "\n\n";

               io << S_PRESS_ENTER_TO_CONTINUE;
            }
         }
      }
   }


   if(user.level<1)
   {
      LOG("Access denied (Level 0 - Locked out)");

      io << '\n' << S_LOCKED_OUT << "\n\n" << S_HANGING_UP << '\xFF';

      Delay(2000);

      throw TXQuit();
   }

   if(user.fileArea <= 0) user.fileArea = 1;
   if(user.msgArea  <= 0) user.msgArea  = 1;

   if(cfg.discrete && !strcmpl(user.name,cfg.sysopName)) user.uFlags |= UFLAG_HIDDEN;

/*
   if(user.uFlags & UFLAG_ATTEN)
      if(playsong("ATTEN","\x1b",0)==1)
      {
         for(i=0;i<5;i++)
         {
            sound(WORD(1000+i*400));
            msleep(100);
         }

         nosound();
      }
*/

   return 0;
}

bool
NewUser(char *username)  // returns record number of user.
{
   if(!cfg.newUserLevel)
   {
      if(mShowAnsiFile("PRIVATE") == SENDFILE_NOTFOUND)
         io << "\n\n"
            << S_PRIVATE_SYSTEM << "\n\n"
            << S_HANGING_UP << '\xFF';

      Delay(2000);

      LOG("Private System - New User rejected");

      throw TXQuit();
   }

/*
   if(cfg.newUserLevel<min_level)
   {
      if(mShowAnsiFile("NOACCESS") == SENDFILE_NOTFOUND)
         io << "\n\n" << S_NOT_FOR_NEW_USERS << "\n\xFF";

      Delay(2000);
      LOG("New user rejected");
      throw TXQuit();
   }
*/

   bool tmp_ansi = (Terminal() == Ansi);

   user.NewUser();
   strcpy(user.language,cfg.defaultLanguage);

   if(tmp_ansi)
      user.uFlags |= UFLAG_ANSI;

   if(cfg.europeanDate)
      user.dateFormat = 2;

   strcpy(user.name,username);

   LOG("Creating new user.");

   mRunPex("/I NEWUSER1");
   mShowAnsiFile("NEWUSER1");

   for(;;)
   {
      int num_languages = 0;

      QDirScan scan(QFileName(SysPath,"*.PBL"));

      for(; scan.operator int() ; scan++ , num_languages++)
         if(QString(scan.name()) == QString("_DEFAULT.PBL"))
            num_languages--;

      if(num_languages > 1)
      {
         io << "\n\n";

         mSelectLanguage("");
      }

      if(cfg.allowAnsi)
      {
         io << "\n\n" << S_ASK_ANSI;

         if(Ask(1))
            user.uFlags |= UFLAG_ANSI;
      }

      if(cfg.allowAvatar)
      {
         io << "\n\n" << S_ASK_AVATAR;

         if(Ask(0))
            user.uFlags |= UFLAG_AVATAR;
      }

      if(Terminal() == Ansi)
      {
         io << "\n\n" << S_ASK_FSED;

         if(Ask(1))
            user.uFlags |= UFLAG_FSED;
      }

      io << "\n\n" << S_ASK_CLS;

      if(Ask(1))
         user.uFlags |= UFLAG_CLEAR;

      io << "\n\n" << S_ASK_PAUSE;

      if(Ask(1))
         user.uFlags |= UFLAG_PAUSE;

      io << "\n\n" << S_ASK_SCREENLENGTH("24");

      char length[3];
      Input(length,2,INPUT_DIGITS);

      user.screenLength=atoi(length);

      if(user.screenLength < 5)
         user.screenLength=24;

      do
      {
         do
         {
            io << "\n\n" << S_ASK_CITY;
            Input(user.city,25);
         }
         while(strlen(user.city)<3);

         if(cfg.askState)
         {
            io << "\n\n" << S_ASK_STATE;
            Input(user.state,25);
         }
      }
      while(cfg.askState && strlen(user.state)<2);

      if(cfg.askCountry)
         do
         {
            io << "\n\n" << S_ASK_COUNTRY;
            Input(user.country,25);
         }
         while(strlen(user.country)<2);


      if(cfg.askAddress)
      {
         io << "\n\n" << S_ASK_MAILING_ADDRESS << "\n\n";

         Input(user.address1,50);
         io << '\n';
         Input(user.address2,50);
         io << '\n';
         Input(user.address3,50);
      }

  if(cfg.askVoicePhone)
    {
     do
       {
        io << "\n\n" << S_ASK_VOICE_PHONE;
        Input(user.voicePhone,15);
       }
        while(strlen(user.voicePhone)<6);
    }

  if(cfg.askDataPhone)
    {
     io << "\n\n" << S_ASK_DATA_PHONE;
     Input(user.dataPhone,15);
    }

  if(cfg.askFaxPhone)
    {
     io << "\n\n" << S_ASK_FAX_PHONE;
     Input(user.faxPhone,15);
    }

  if(cfg.askDateFormat)
  {
     io << "\n\n";

     mChangeDateFormat(NULL);
  }

  if(cfg.askSex)
  {
      io << "\n\n" << S_ASK_SEX;

      char k = WaitLanguageHotkeys(K_ASK_SEX,FALSE);

      user.sex = k+1;

      io << (k ? S_FEMALE:S_MALE);
  }

  if(cfg.askBirthDay)
    do
      {
       io << "\n\n" << S_ASK_BIRTHDATE(DateFormats[user.dateFormat]);

       InputDate(user.birthDate);

       if(!user.birthDate.ok())
         {
            if(cfg.askBirthDay > 1)
              {
               user.birthDate.set(0,0,0);
               break;
              }
             else continue;
         }
      }
       while(!user.birthDate.ok());


  if(cfg.allowAlias)
    {
     for(;;)
       {
        user.alias[0] = 0;
        io << "\n\n" << S_ASK_ALIAS;
        Input(user.alias,30,INPUT_UPFIRST);

        if(!user.alias[0])
         break;

        TpUser tmpuser;
        if(tmpuser.Search(user.alias) || tmpuser.Search(user.alias,TRUE,FALSE,TRUE))
          {
           io << "\n\n" << S_ALIAS_BEING_USED;
           continue;
          }
         else break;
       }
    }

  char pass[16];

   for(;;)
   {
      io << "\n\n" << S_ASK_PASSWORD(form("%d",cfg.minPasswordLength),"15");

      Input(user.passWord,15,INPUT_PWD);
      if(strlen(user.passWord) < cfg.minPasswordLength)
      {
         io << "\n\n" << S_ILLEGAL_PASSWORD;
         continue;
      }

      io << "\n\n" << S_ASK_PASSWORD_AGAIN;

      Input(pass,15,INPUT_PWD);

      if(!strcmpl(pass,user.passWord))
         break;
   }

  PasswordOk = TRUE;

  user.level    = cfg.newUserLevel;
  user.logLevel = cfg.newUserLogLevel;
  user.aFlags   = cfg.newUserFlags;

  io << "\n\n\n" << S_ASK_EVERYTHING_CORRECT;

  if(Ask(1))
   break;
  else
   LOG("Missed some questions, reentering...");
  }

user.uFlags |= UFLAG_HOTKEYS;
user.fileArea = 1;
user.msgArea = 1;

io << '\n';

LOG("New user created.");

mRunPex("/I NEWUSER2");
mShowAnsiFile("NEWUSER2");

mQuestionnaire("NEWUSER");

   user.lastDate.today();
   user.lastTime.now();
   user.firstDate.today();
   user.lastNewFilesCheck.today();

   return user.Write(TRUE);
}

bool
CheckTrashCan(char *username)
{
   QFile f;

   if(!f.open(QFileName(SysPath,"TRASHCAN.CTL"),fmode_read | fmode_text)) return FALSE;

   for(;;)
   {
      char s[80];

      if(!f.readLine(s,79))
         return FALSE;

      strip_linefeed(s);

      if(!strcmpl(s,username))
         return TRUE;
   }
}

