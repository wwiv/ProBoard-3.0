#include "proboard.hpp"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

void
KillLanguage()
{
   if(lang)
   {
      delete [] lang;
   }

   lang = NULL;
   NumLanguageStrings = 0;
}

bool
ReadLanguage( char *langname )
{
   if(langname == NULL)
   {
      KillLanguage();

      return FALSE;
   }

   QFileName fn(SysPath , langname , ".PBL");
   QFile f;

   if(!f.open(fn , fmode_read , 4096))
   {
      LOG("ERROR: Unable to read language file %s",(char *)fn);

      return FALSE;
   }

   if(f.read(&CurrentLanguage , sizeof(TpLanguageFile)) != sizeof(TpLanguageFile))
   {
      LOG("Error reading language file <%s>" , (char *)fn);

      return FALSE;
   }

   if(strlen(CurrentLanguage.menuPath) < 3)
      CurrentLanguage.menuPath[0] = '\0';

   if(strlen(CurrentLanguage.txtPath) < 3)
      CurrentLanguage.txtPath[0] = '\0';

   if(strlen(CurrentLanguage.questPath) < 3)
      CurrentLanguage.questPath[0] = '\0';

   if(CurrentLanguage.menuPath[0])
      append_backspace(CurrentLanguage.menuPath);

   if(CurrentLanguage.txtPath[0])
      append_backspace(CurrentLanguage.txtPath);

   if(CurrentLanguage.questPath[0])
      append_backspace(CurrentLanguage.questPath);

   KillLanguage();

   f >> NumLanguageStrings;

   lang = new _TpLanguageString[NumLanguageStrings];

   for(int i=0;i<NumLanguageStrings;i++)
   {
      if(!lang[i].read(f)) break;

      QString str;

      if(!(lang[i].flags & LANG_NOCOLOR))
         str << char(26) << char(lang[i].color);

      char *s = lang[i].s;

      bool high = FALSE;

      bool akrol_found = FALSE;
      bool pex_found   = FALSE;
      bool ans_found   = FALSE;
      bool last_was_ansi=FALSE;

      QString ans_pex_name;

      for(;*s;s++)
      {
         last_was_ansi = FALSE;

         if(akrol_found)
         {
            if(*s != 'p' && *s != 'a')
            {
               str << '@' << *s;
            }
            else
            {
               if(*s == 'p')
                  pex_found = TRUE;
               else
                  ans_found = TRUE;

               ans_pex_name = "";
            }

            akrol_found = FALSE;

            continue;
         }

         if(pex_found || ans_found)
         {
            if(*s == '@')
            {
               str << (pex_found ? char(24):char(25)) << char(ans_pex_name.len()) << ans_pex_name;

               pex_found = ans_found = FALSE;

               last_was_ansi = TRUE;
            }
            else
            {
               ans_pex_name << *s;
            }

            continue;
         }

         if(*s == '^')
         {
            high = !high;

            if(high)
               str << char(26) << char(lang[i].highlight);
            else
               str << char(26) << char(lang[i].color);
         }
         else
         {
            if(*s == '\\')
            {
               char c = *(++s);

               if(c == '\\' || c == '^')
               {
                  str << c;

                  continue;
               }
               else
               {
                  BYTE col = 0;

                  if(isxdigit(c))
                  {
                     for( int i = 0; i < 2 ; i++ , s++)
                     {
                        c = *s;

                        if(isdigit(c))
                           col = col * 16 + c - '0';
                        else
                           col = col * 16 + toupper(c) - 'A' + 10;
                     }

                     str << char(26) << char(col);

                     s--;

                     continue;
                  }

                  if(c == 'H' || c == 'L')
                  {
                     switch(*(++s))
                     {
                        case 'B': col = 1;
                                 break;
                        case 'G': col = 2;
                                 break;
                        case 'C': col = 3;
                                 break;
                        case 'R': col = 4;
                                 break;
                        case 'P': col = 5;
                                 break;
                        case 'Y': col = 6;
                                 break;
                        case 'W': col = 7;
                                 break;
                     }

                     if(c == 'H') col |= 8;
                  }

                  str << char(26) << char(col);

                  continue;
               }
            }

            if(*s == '@')
            {
               akrol_found = TRUE;
               continue;
            }

            str << (*s);
         }
      }


      if(lang[i].flags & LANG_PROMPT)
      {
         if(!last_was_ansi)
            str << ' ';

         str << char(26) << char(lang[i].promptcolor);
      }

      delete [] lang[i].s;

      lang[i].len = str.len();
      lang[i].s   = new char[ lang[i].len + 2 ];   // To accomodate for '\t' (below)

      strcpy(lang[i].s , str);
   }

   f.close();

   strcat(S_PRESS_ENTER_TO_CONTINUE,"\t");

   return TRUE;
}

char
WaitLanguageHotkeys(char *hk, bool enter)
{
   QString hotkeys;

   hotkeys = hk;
   if(enter)
      hotkeys << '\r';

   char k = WaitKeys(hotkeys);

   k = hotkeys.find(QString(char(k)));

   if(hotkeys[(int)k] == char('\r'))
      return '\r';
   else
      return k;
}

int
LanguageStringLength( char *str )
{
   int l = 0;

   for( ; *str ; str++)
   {
      char c = *str;

      if(c == char(26))
      {
         str++;
         continue;
      }

      l++;
   }

   return l;
}
