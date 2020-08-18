/***************************************************************************
 class QFileName

 Compatibility: DOS, OS/2, Windows
 Models       : 16 bit - 32 bit
***************************************************************************/

#ifdef PEX
  #include <pb_sdk.h>
#else
  #include <string.h>
#endif

#include "tslib.hpp"

QFileName::QFileName(const char *p,const char *f,const char *e) : QString(p)
{
   if(f) (*this) << f;
   if(e) (*this) << e;
}

void
QFileName::operator()(const char *p)
{
   clear();

   if(p) (*this) << p;
}

void
QFileName::operator()(const char *p,const char *f)
{
   clear();
   if(p) (*this) << p;
   if(f) (*this) << f;
}

void
QFileName::operator()(const char *p,const char *f,const char *e)
{
   clear();
   if(p) (*this) << p;
   if(f) (*this) << f;
   if(e) (*this) << e;
}

void
QFileName::stripPath()
{
   int l=len();
   for(int i=l-1;i>=0;i--)
   {
      if(s[i]=='\\' || s[i]=='/' || s[i]==':') break;
   }

   if(i >= 0) del(0,i+1);
}

void
QFileName::appendBS()
{
   int l=len();

   if(s[l-1]!='\\') (*this) << '\\';
}

void
QFileName::stripExt()
{
   int l=len();

   for(int i=l-1 ; i>=0 ; i--)
   {
      if(s[i] == '\\' || s[i] == ':')
         break;

      if(s[i] == '.')
      {
         del(i,l-i);
         break;
      }
   }
}

void
QFileName::stripName()
{
   int l=len();

   for(int i=l-1;i>=0;i--)
      if(s[i]=='\\' || s[i]=='/' || s[i]==':')
      {
         del(i+1,l-i-1);
         break;
      }
}

void
QFileName::changeExt(const char *ext)
{
   stripExt();

   (*this) << '.' << ext;
}

void
QFileName::changePath(const char *p)
{
   stripPath();

   QFileName tmp = *this;

   *this = p;
   appendBS();

   *this << tmp;
}

void
QFileName::operator=(const char *s)
{
   QString::operator=(s);
}

void
QFileName::operator=(const QFileName& fn)
{
   QString::operator=((QString)fn);
}

void
QFileName::operator=(char c)
{
   QString::operator=(c);
}

void
QFileName::operator=(int i)
{
   QString::operator=(i);
}

void
QFileName::operator=(long l)
{
   QString::operator=(l);
}

void
QFileName::fit(int size)
{
    if(len() > size)
    {
        QString p(s);
        int pos = p.find("\\");
        p.insert(pos + 1, "...\\");

        pos += 4;
        while(p.len() > size)
        {
            for(int i = 1; p[pos + i] != '\\' && p[pos + i] != 0; i++);

            if(p[pos + i] == 0)
                break;

            if(p[pos + i] == '\\')
                p.del(pos + 1, i);
        }

        (*this) = p;
    }
}
