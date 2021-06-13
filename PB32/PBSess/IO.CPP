#include "proboard.hpp"
#include <ctype.h>
#include <stdlib.h>


void
Send(BYTE c)
{
   if(c == '\f')
      FullColor(0x0F);

   if(c == '\n')
      Send('\r');

   (*cbSend)(c);
}

void
WaitKey(BYTE c)
{
   while(toupper((*cbWaitKey)()) != toupper(c)) {}
}

BYTE
WaitKeys(BYTE *s)
{
   strupr((char *)s);

   for(;;)
   {
      BYTE k = (BYTE)toupper(WaitKey());

      if(strchr((char *)s,k)) return k;
   }
}

void
Cls()
{
   io << '\f' << char(0xFF);
}


BYTE
Send(char *str,char *hotkeys)
{
   if(hotkeys)
      strupr(hotkeys);

   for(;*str;str++)
   {
      BYTE c = 0;

      //if(SCREEN.inEscape())
      //{
      //   io << (*str);
      //
      //   continue;
      //}

      if(hotkeys)
         c = (BYTE) toupper(ReadKey());

      if(hotkeys && c)
         if(strchr(hotkeys,c))
         {
            return c;
         }

      if(c=='S')
      {
         OutputStopped = TRUE;
         FlushOutput();

         return 1;
      }

      if(c=='P')
         WaitKeys((BYTE *)"P\r");

      c = *str;

      if(c=='\t')
      {
         WaitKey('\r');

         continue;
      }

      if(c == 26)
      {
         FullColor(*(++str));
         continue;
      }

      if(c<8 && c>0)
      {
         Color(c);

         continue;
      }

      if(c == 24 || c == 25)
      {
         int l = int(*(str+1));
         char *fname = new char[l+1];
         strncpy(fname,str+2,l);
         fname[l] = '\0';

         if(c == 24)
            mRunPex(fname);
         else
            ShowAnsiFile(fname);

         str += l+1;

         delete [] fname;

         continue;
      }

      if(c<0x18 && c>0x10 && c!=0x16)
      {
         Color((c-0x10)|0x80);
      }
      else
      {
         io << c;
      }
   }

   return 0;
}


void
Input(char *s,int max,BYTE mode)
{
   char k;

   if(!(mode & INPUT_NOFIELD))
      DrawField(max);

   int i = 0;

   while((k=WaitKey()) != 13)
   {
      if(k==27 || k==10 || k==9)
         continue;

      if(k==8)
      {
         if(i>0)
         {
            i--;
            io << "\b \b";
         }
      }
      else
      {
         if(i<max && (isprint(k) || (k & 0x80)))
         {
            switch(mode & 7)
            {
               case INPUT_ALL    :
                  break;

               case INPUT_DIGITS :
                  if(!isdigit(k))
                     continue;
                  break;

               case INPUT_UPFIRST:
                  if(s[i-1]=='.' ||  s[i-1]==' ' ||  s[i-1]=='-' || i==0)
                     k = (char)toupper(k);
                  else
                     k = (char)tolower(k);
                  break;

               case INPUT_UPALL  :
                  k = (char)toupper(k);
            }

            s[i++] = k;

            if(mode &  INPUT_PWD)
               io << '*';
            else
               io << k;
         }
      }
   }

   io << '\r';

   s[i] = '\0';

   switch(Terminal())
   {
      case Avatar:
         io << char(22) << char(1) << char(CurrentAttribute() & 0x0F);
         break;
      case Ansi  :
         io << "\x1b[40m";
         break;
   }

   FlushOutput();
}



int
Input(int& i,int len)
{
   long l;
   int ret = Input(l,(len<5)?len:5);

   if(ret >= 0) i = int(l);

   return ret;
}

int
Input(long& i,int len)
{
   char s[10];

   Input(s,(len<10)?len:10,INPUT_DIGITS);

   if(!s[0]) return -1;

   i = atol(s);

   return 0;
}


void
DrawField(int max)
{
   int i;

   if(Terminal() == Ansi || Terminal() == Avatar)
   {
      FullColor(((CurrentAttribute()) & BYTE(0xF)) | BYTE(1<<4));

      if(Terminal() != Avatar)
      {
         for(i=0;i<max;i++)
            io << ' ';

         io << form("\x1b[%dD",max);
      }
      else
      {
         io << char(25) << ' ' << char(max);

         for(i = 0;i<max;i++)
            io << '\b';
      }
   }
}

QString
FullColorString(BYTE x)
{
   QString str;

   switch(Terminal())
   {
      case TTY:
         break;

      case Avatar:
         {
            str << char(22) << char(1) << char(x & 0x7F);

            if(x & 0x80)
               str << char(22) << char(2);
         }
         break;

      case Ansi:
      {
         static char colors[] = { 0,4,2,6,1,5,3,7 };

         int fg = colors[x&7];
         int bg = colors[(x>>4)&7];
         int blink = (x & 0x80) ? 1:0;
         int high  = (x & 0x08) ? 1:0;

         str << char(27) << "[0;";

         if(high)
            str << "1;";
         if(blink)
            str << "5;";

         str << form("%d;%dm",fg+30,bg+40);
      }
   }

   return str;
}


void
FullColor(BYTE c)
{
   io << FullColorString(c);
}

void
Color(BYTE c)
{
   QString s;
   int blink=(int)(c & 0x80);
   c &= 0x7;

   switch(Terminal())
   {
      case Avatar:
         {
            static char colors[] = { 0,4,2,6,1,5,3,7 };


            s << char(22) << char(1);
            s << char(colors[c]|8);

            if(blink) s << char(22) << char(2);
         }
         break;

      case Ansi:
         {
            s = "\x1b[0;1;3";

            s << (char)(c+'0');

            if(blink) s << ";5";

            s << 'm';

         }
         break;

      default:
         return;
   }

   for(int i=0;s[i];i++)
      io << s[i];
}

BYTE
SendFile(char *fn,char *hotkeys)
{
   bool  fflag       = false,
         kflag       = false,
         moreok      = true,
         stopok      = true,
         avt_compr   = false;

   QString::justification alignment = QString::left;

   QString str;

   int fieldwidth = 0;

   BYTE avt_compr_char = '\0';

   QFile f(fn,fmode_read,1024);

   if(!f.opened())
      return SENDFILE_NOTFOUND;

   if(hotkeys)
      strupr(hotkeys);

   if(pLineCountHandler)
      (*pLineCountHandler)(0);

   for(;;)
   {
      BYTE c;

      if((c = ReadKey()) != 0)
      {
         c = BYTE(toupper(c));

         if(hotkeys)
            if(strchr(hotkeys,c))
               return c;

         if(c=='S' && stopok)
         {
            return SENDFILE_INTERRUPTED;
         }

         if(c=='P') WaitKeys("\rP");
      }

      int x = f.readByte();

      if(x < 0)
         break;

      BYTE input = BYTE(x);

      if(avt_compr)
      {
         if(fflag || kflag)
         {
            if(!avt_compr_char)
            {
               avt_compr_char = input;
            }
            else
            {
               if(avt_compr_char=='@' || avt_compr_char=='#' || avt_compr_char=='%')
               {
                  fieldwidth += input;

                  switch(avt_compr_char)
                  {
                     case '@': alignment = QString::left;     break;
                     case '#': alignment = QString::right;    break;
                     case '%': alignment = QString::centered; break;
                  }
               }

               avt_compr = false;
            }
         }
         else
         {
            avt_compr = false;

            io << char(25) << input;
         }

         continue;
      }

      //if(SCREEN.inEscape())
      //{
      //   io << input;
      //
      //   continue;
      //}

      if(input == 0x19)
      {
         avt_compr      = true;
         avt_compr_char = '\0';

         continue;
      }

      if((fflag || kflag) && (input=='@' || input=='#' || input=='%'))
      {
         fieldwidth++;

         switch(input)
         {
            case '@': alignment = QString::left;     break;
            case '#': alignment = QString::right;    break;
            case '%': alignment = QString::centered; break;
         }

         continue;
      }


      if(fflag || kflag)
      {
         if(pControlCodeHandler)
	    str = (*pControlCodeHandler)( fflag ? BYTE('') : BYTE('') , input , fieldwidth , alignment);
         else
            str.clear();

         fflag      = false;
         kflag      = false;

         fieldwidth = 0;

         io << str;

         continue;
      }

      if(input<27)
      {
         switch(input)
         {
            case  1: WaitKey('\r');
                     break;
            case  2: stopok = false;
                     break;
            case  3: stopok = true ;
                     break;
            case  4: moreok = true ;
                     break;
            case  5: moreok = false;
                     break;
            case  6: fflag      = true;
                     fieldwidth = 2;
                     break;
            case 10: io << input;
                     if(moreok)
                        if(pLineCountHandler)
                           if((*pLineCountHandler)(-1))
                              return 1;
                     break;
            case 11: kflag      = true;
                     fieldwidth = 2;
                     break;
            case 17: break;                         // XON/XOFF
            case 19: break;                         // XON/XOFF
            case 23: Delay(1000);
                     break;
            case 24: break;
            case 26: break;                         // EOF
            default: kflag = fflag = false;
                     io << input;
                     break;
         }
      }
      else
      {
         io << input;
      }
   }

   return SENDFILE_OK;
}

int
Ask(int def)
{
   int ret;
   QString keys;

   if(def)
   {
      io << S_ASK_YES_NO;
      keys = K_ASK_YES_NO;
   }
   else
   {
      io  << S_ASK_NO_YES;
      keys = K_ASK_NO_YES;
   }

   keys << '\r';

   char k = WaitKeys(keys);

   if(k == keys[0])
      ret = TRUE;

   if(k == keys[1])
      ret = FALSE;

   if(k == keys[2])
      ret = def;

   if(ret)
      io << S_YES;
   else
      io << S_NO;

   io << char(0xFF);

   return ret;
}


void
FlushOutput()
{

}


int
LineCounter(int reset)  // reset=-1 -> increment
{
   if(reset>=0)
   {
      LineCount = reset;
      OutputContinuous = FALSE;
      return 0;
   }

   if(++LineCount>=((user.screenLength)-1) && !OutputContinuous && (user.uFlags & UFLAG_PAUSE))
   {
      char rep;

      if(pMoreFunction)
      {
      rep = char((*pMoreFunction)());
      }
      else
      {
         BYTE oldcolor=CurrentAttribute();

         io << S_MORE;

         int prompt_len = strlen(S_MORE);

         rep = WaitLanguageHotkeys(K_MORE);

         io << '\r' << QString(' ',prompt_len) << '\r';

         FullColor(oldcolor);
      }

      if(rep == '\r')
         rep = 0;

      if(rep == 2)
      {
         OutputContinuous = TRUE;
         rep = 0;
      }

      LineCount=0;

      return rep;
   }

   return 0;
}

void
EnableStop()
{
   StopEnabled   = TRUE;
   OutputStopped = FALSE;
}

void
DisableStop()
{
   StopEnabled = OutputStopped = FALSE;
}

void
FlushInput()
{
   while(ReadKey());
}
