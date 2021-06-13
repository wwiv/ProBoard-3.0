#include "proboard.hpp"

#include <string.h>
#include <stdlib.h>


const int OFF     = 0;
const int ON      = 1;
const int TOGGLE  = 2;
const int ASK     = 3;
const int NONE    = 4;
const int SAVE    = 0x10;
const int RESTORE = 0x20;
const int QUIET   = 0x40;

static int
toggle_type(char *data)
{
   QString param[5];
   int ret=TOGGLE;
   char *strings[] = { "OFF", "ON" , "TOGGLE" , "ASK" , "SAVE" , "RESTORE" , "/Q", NULL };

   int num_para = ParseData(data,param);

   for(int i=0;i<num_para;i++)
   {
     int j;
      for(j=0;strings[j];j++) if(param[i].stricmp(strings[j])) break;

      if(!strings[j]) continue;

      switch(j)
      {
         case 0:
         case 1:
         case 2:
         case 3: ret = j;
                 break;
         case 4: ret |= SAVE;
                 break;
         case 5: ret |= RESTORE;
                 break;
         case 6: ret |= QUIET;
                 break;
      }
   }

   if(ret == NONE)
      ret = TOGGLE;

   return ret;
}


int
mChangeCity(char *)
{
   io << "\f\n" << S_CHANGE_CITY_TITLE_AND_PROMPT(user.city);

   char tmp[26];

   Input(tmp,25);

   if(strlen(tmp)<2) return 1;

   strcpy(user.city,tmp);

   LOG(1,"City changed to '%s'",user.city);
   return 0;
   }

int
mChangeVoicePhone(char *)
{
   io << "\f\n" << S_CHANGE_VOICE_PHONE_TITLE_AND_PROMPT(user.voicePhone);

   char tmp[16];

   Input(tmp,15);

   if(strlen(tmp)<5) return 0;

   strcpy(user.voicePhone,tmp);

   LOG(1,"Voice Phone # changed to '%s'",user.voicePhone);
   return 0;
   }

int
mChangeDataPhone(char *)
{
   io << "\f\n" << S_CHANGE_DATA_PHONE_TITLE_AND_PROMPT(user.dataPhone);

   char tmp[16];

   Input(tmp,15);

   if(strlen(tmp)<5) return 0;

   strcpy(user.dataPhone,tmp);

   LOG(1,"Data Phone # changed to '%s'",user.dataPhone);
   return 0;
   }

int
mChangeFaxPhone(char *)
{
   io << "\f\n" << S_CHANGE_FAX_PHONE_TITLE_AND_PROMPT(user.faxPhone);

   char tmp[16];

   Input(tmp,15);

   if(strlen(tmp)<5) return 0;

   strcpy(user.faxPhone,tmp);

   LOG(1,"Fax Phone # changed to '%s'",user.faxPhone);
   return 0;
   }


int
mChangeState(char *)
{
   io << "\f\n" << S_CHANGE_STATE_TITLE_AND_PROMPT(user.state);

   char tmp[26];

   Input(tmp,25);

   if(strlen(tmp)<2) return 0;

   strcpy(user.state,tmp);

   LOG(1,"State changed to '%s'",user.state);
   return 0;
   }

int
mChangeCountry(char *)
{
   io << "\f\n" << S_CHANGE_COUNTRY_TITLE_AND_PROMPT(user.country);

   char tmp[26];

   Input(tmp,25);

   if(strlen(tmp)<3) return 0;

   strcpy(user.country,tmp);

   LOG(1,"Country changed to '%s'",user.country);
   return 0;
   }


int
mChangeAddress(char *)
{
   io << "\f\n" << S_CHANGE_MAILING_ADDRESS_TITLE_AND_PROMPT((char *)(QString(user.address1)+"\n"+QString(user.address2)+"\n"+QString(user.address3)));

   char tmp[51];

   io << "\n\n";
   Input(tmp,50);

   if(!tmp[0])
      return 0;

   strcpy(user.address1,tmp);

   io << '\n';
   Input(user.address2,50);
   io << '\n';
   Input(user.address3,50);

   LOG(1,"Mailing address changed");

   return 0;
}


int
mChangeHandle(char *)
{
   io << "\f\n" << S_CHANGE_ALIAS_TITLE_AND_PROMPT(user.alias);

   char tmp[36];

   Input(tmp,35,INPUT_UPFIRST);

   if(strlen(tmp)<3) return 0;

   TpUser x;

   long a_rec=-1,u_rec=-1;
   bool a_found = x.Search(tmp,TRUE,FALSE,TRUE);
   if(a_found) a_rec = x.record;
   bool u_found = x.Search(tmp);
   if(u_found) u_rec = x.record;

   if(!strcmpl(tmp,"Sysop") || (a_rec>=0 && a_rec!=user.record) || (u_rec>=0 && u_rec!=user.record))
   {
      LOG(1,"Duplicate alias: '%s'",tmp);

      io << "\n\n" << S_ALIAS_BEING_USED << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
      return 1;
   }

   strcpy(user.alias,tmp);

   LOG(1,"Alias changed to '%s'",user.alias);
   return 0;
   }


int
mChangePassword(char *)
{
   char pass[16];

   io << "\f\n" << S_CHANGE_PASSWORD_TITLE;

   do
   {
      io << "\n\n" << S_ENTER_NEW_PASSWORD(form("%d",cfg.minPasswordLength));

      Input(pass,15,INPUT_PWD);

      if(strlen(pass)<cfg.minPasswordLength)
      {
         io << "\n\n" << S_ILLEGAL_PASSWORD << '\n';
         Delay(2000);
         return 1;
      }

      io << "\n\n" << S_ASK_PASSWORD_AGAIN;

      Input(user.passWord,15,INPUT_PWD);
   }
   while(strcmpl(pass,user.passWord));

   user.passWordCRC = RaCrc(user.passWord);

   io << "\n\n" << S_PASSWORD_CHANGED_SUCCESSFULLY << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;

   LOG(1,"PassWORD changed to '%s'",user.passWord);

   return 0;
}

int
mChangeScreenLines(char *)
{
   char newlen[4];

   io << "\f\n" << S_CHANGE_SCREENLENGTH_TITLE_AND_PROMPT(form("%d",user.screenLength));

   Input(newlen,2,INPUT_DIGITS);

   if(atoi(newlen) >= 5)
      user.screenLength = atoi(newlen);

   LOG(1,"Screenlength changed to %d",user.screenLength);

   return 0;
}

#define TOGGLE_DISPLAY(var)  { io << ((var) ? string_enabled : string_disabled); io << S_PRESS_ENTER_TO_CONTINUE; }

int
mToggleAnsi(char *data)
{
 static bool prev = FALSE;

 int action = toggle_type(data);

 if(action & SAVE) prev = (user.uFlags & UFLAG_ANSI) ? TRUE:FALSE;

 switch(action & 0xF)
   {
    case ON    : user.uFlags |= UFLAG_ANSI;
                 break;
    case OFF   : user.uFlags &= ~UFLAG_ANSI;
                 break;
    case TOGGLE: user.uFlags ^= UFLAG_ANSI;
                 break;
    case ASK   : io << '\n' << S_ASK_ANSI;
                 if(Ask()) user.uFlags |= UFLAG_ANSI;
                         else
                           {
                            if(user.uFlags & UFLAG_ANSI) io << "\x1b[0m";
                            user.uFlags &= ~UFLAG_ANSI;
                           }
                 io << '\n';
                 break;
   }

 if(action & RESTORE)
   {
    if(prev) user.uFlags |= UFLAG_ANSI;
        else user.uFlags &= ~UFLAG_ANSI;
   }

 if(!(action & QUIET))
   {
    if(user.uFlags & UFLAG_ANSI) LOG(1,"ANSI enabled");
             else LOG(1,"ANSI disabled");

    if(user.uFlags & UFLAG_ANSI)
      io << '\n' << S_ANSI_ENABLED;
    else
      io << '\n' << S_ANSI_DISABLED;

     io << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
   }

 MenuStack.Update = TRUE;
   return 0;
   }

int
mToggleAvatar(char *data)
{
 static bool prev = FALSE;

 int action = toggle_type(data);

 if(action & SAVE) prev = (user.uFlags & UFLAG_AVATAR) ? TRUE:FALSE;

 switch(action & 0xF)
   {
    case ON    : user.uFlags |= UFLAG_AVATAR;
                 break;
    case OFF   : user.uFlags &= ~UFLAG_AVATAR;
                 break;
    case TOGGLE: user.uFlags ^= UFLAG_AVATAR;
                 break;
    case ASK   : io << '\n' << S_ASK_AVATAR;
                 if(Ask()) user.uFlags |= UFLAG_AVATAR;
                         else user.uFlags &= ~UFLAG_AVATAR;
                 io << '\n';
                 break;
   }

 if(action & RESTORE)
   {
    if(prev) user.uFlags |= UFLAG_AVATAR;
        else user.uFlags &= ~UFLAG_AVATAR;
   }

 if(!(user.uFlags & UFLAG_AVATAR)) user.uFlags &= ~UFLAG_AVTPLUS;

 if(!(action & QUIET))
   {
    if(user.uFlags & UFLAG_AVATAR) LOG(1,"AVATAR enabled");
          else LOG(1,"AVATAR disabled");

    if(user.uFlags & UFLAG_AVATAR)
      io << '\n' << S_AVATAR_ENABLED;
    else
      io << '\n' << S_AVATAR_DISABLED;

     io << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
   }

 MenuStack.Update = TRUE;
   return 0;
   }

int
mToggleCls(char *data)
{
 static bool prev = FALSE;

 int action = toggle_type(data);

 if(action & SAVE) prev = (user.uFlags & UFLAG_CLEAR) ? TRUE:FALSE;

 switch(action & 0xF)
   {
    case ON    : user.uFlags |= UFLAG_CLEAR;
                 break;
    case OFF   : user.uFlags &= ~UFLAG_CLEAR;
                 break;
    case TOGGLE: user.uFlags ^= UFLAG_CLEAR;
                 break;
    case ASK   : io << '\n' << S_ASK_CLS;
                 if(Ask()) user.uFlags |= UFLAG_CLEAR;
                         else user.uFlags &= ~UFLAG_CLEAR;
                 io << '\n';
                 break;
   }

 if(action & RESTORE)
   {
    if(prev) user.uFlags |= UFLAG_CLEAR;
        else user.uFlags &= ~UFLAG_CLEAR;
   }

 if(!(action & QUIET))
   {
    if(user.uFlags & UFLAG_CLEAR) LOG(1,"Screen clearing enabled");
            else LOG(1,"Screen clearing disabled");

    if(user.uFlags & UFLAG_CLEAR)
      io << '\n' << S_CLS_ENABLED;
    else
      io << '\n' << S_CLS_DISABLED;

     io << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
   }

 MenuStack.Update = TRUE;
   return 0;
   }

int
mTogglePause(char *data)
{
 static bool prev = FALSE;

 int action = toggle_type(data);

 if(action & SAVE) prev = (user.uFlags & UFLAG_PAUSE) ? TRUE:FALSE;

 switch(action & 0xF)
   {
    case ON    : user.uFlags |= UFLAG_PAUSE;
                 break;
    case OFF   : user.uFlags &= ~UFLAG_PAUSE;
                 break;
    case TOGGLE: user.uFlags ^= UFLAG_PAUSE;
                 break;
    case ASK   : io << '\n' << S_ASK_PAUSE;
                 if(Ask()) user.uFlags |= UFLAG_PAUSE;
                         else user.uFlags &= ~UFLAG_PAUSE;
                 io << '\n';
                 break;
   }

 if(action & RESTORE)
   {
    if(prev) user.uFlags |= UFLAG_PAUSE;
        else user.uFlags &= ~UFLAG_PAUSE;
   }

 if(!(action & QUIET))
   {
    if(user.uFlags & UFLAG_PAUSE) LOG(1,"Page pausing enabled");
              else LOG(1,"Page pausing disabled");

    if(user.uFlags & UFLAG_PAUSE)
      io << '\n' << S_PAUSE_ENABLED;
    else
      io << '\n' << S_PAUSE_DISABLED;

     io << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
   }

 MenuStack.Update = TRUE;
   return 0;
   }

int
mToggleFsEd(char *data)
{
 static bool prev = FALSE;

 int action = toggle_type(data);

 if(action & SAVE) prev = (user.uFlags & UFLAG_FSED) ? TRUE:FALSE;

 switch(action & 0xF)
   {
    case ON    : user.uFlags |= UFLAG_FSED;
                 break;
    case OFF   : user.uFlags &= ~UFLAG_FSED;
                 break;
    case TOGGLE: user.uFlags ^= UFLAG_FSED;
                 break;
    case ASK   : io << '\n' << S_ASK_FSED;
                 if(Ask()) user.uFlags |= UFLAG_FSED;
                         else user.uFlags &= ~UFLAG_FSED;
                 io << '\n';
                 break;
   }

 if(action & RESTORE)
   {
    if(prev) user.uFlags |= UFLAG_FSED;
        else user.uFlags &= ~UFLAG_FSED;
   }

 if(!(action & QUIET))
   {
    if(user.uFlags & UFLAG_FSED) LOG(1,"FsEd enabled");
             else LOG(1,"FsEd disabled");

    if(user.uFlags & UFLAG_FSED)
      io << '\n' << S_FSED_ENABLED;
    else
      io << '\n' << S_FSED_DISABLED;

     io << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
   }

 MenuStack.Update = TRUE;
   return 0;
   }

int
mToggleHotkeys(char *data)
{
 static bool prev = FALSE;

 int action = toggle_type(data);

 if(action & SAVE) prev = (user.uFlags & UFLAG_HOTKEYS) ? TRUE:FALSE;

 switch(action & 0xF)
   {
    case ON    : user.uFlags |= UFLAG_HOTKEYS;
                 break;
    case OFF   : user.uFlags &= ~UFLAG_HOTKEYS;
                 break;
    case TOGGLE: user.uFlags ^= UFLAG_HOTKEYS;
                 break;
    case ASK   : io << '\n' << S_ASK_HOTKEYS;
                 if(Ask()) user.uFlags |= UFLAG_HOTKEYS;
                         else user.uFlags &= ~UFLAG_HOTKEYS;
                 io << '\n';
                 break;
   }

 if(action & RESTORE)
   {
    if(prev) user.uFlags |= UFLAG_HOTKEYS;
        else user.uFlags &= ~UFLAG_HOTKEYS;
   }

 if(!(action & QUIET))
   {
    if(user.uFlags & UFLAG_HOTKEYS) LOG(1,"Hotkeys enabled");
              else LOG(1, "Hotkeys disabled");

    if(user.uFlags & UFLAG_HOTKEYS)
      io << '\n' << S_HOTKEYS_ENABLED;
    else
      io << '\n' << S_HOTKEYS_DISABLED;

     io << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
   }

 MenuStack.Update = TRUE;
   return 0;
   }

int
mToggleIBM(char *data)
{
 static bool prev = FALSE;

 int action = toggle_type(data);

 if(action & SAVE) prev = (user.uFlags & UFLAG_NOIBM) ? TRUE:FALSE;

 switch(action & 0xF)
   {
    case OFF   : user.uFlags |= UFLAG_NOIBM;
                 break;
    case ON    : user.uFlags &= ~UFLAG_NOIBM;
                 break;
    case TOGGLE: user.uFlags ^= UFLAG_NOIBM;
                 break;
    case ASK   : io << '\n' << S_ASK_IBMCHARS;
                 if(!Ask()) user.uFlags |= UFLAG_NOIBM;
                          else user.uFlags &= ~UFLAG_NOIBM;
                 io << '\n';
                 break;
   }

 if(action & RESTORE)
   {
    if(prev) user.uFlags |= UFLAG_NOIBM;
        else user.uFlags &= ~UFLAG_NOIBM;
   }

 if(!(action & QUIET))
   {
    if(user.uFlags & UFLAG_NOIBM)
         LOG(1,"IBM graphics disabled");
    else
         LOG(1,"IBM graphics enabled");

    if(!(user.uFlags & UFLAG_NOIBM))
      io << '\n' << S_IBMCHARS_ENABLED;
    else
      io << '\n' << S_IBMCHARS_DISABLED;

     io << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
   }

 MenuStack.Update = TRUE;
   return 0;
   }


int
mListUsers(char *data)
{
   bool aliases = FALSE;

   char s[40];

   if(QString(data) == QString("/H"))
      aliases = TRUE;

   io << "\f\n" << S_LIST_USERS_TITLE_AND_PROMPT;

   Input(s,39,INPUT_UPALL);

   LOG(2,"User list requested. Search for \"%s\"",s);

   io << "\n\f";

   //x user.list(s,aliases);

   io << '\n' << S_END_OF_USER_LIST << ' ' << S_PRESS_ENTER_TO_CONTINUE;
   return 0;
   }

