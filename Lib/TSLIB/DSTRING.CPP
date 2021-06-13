/***************************************************************************
 class QString

 Compatibility: DOS, OS/2, Windows
 Models       : 16/32 bit
***************************************************************************/

#ifdef PEX
  #include <pb_sdk.h>
#else
  #include <stdlib.h>
  #include <stdio.h>
  #include <ctype.h>
  #include <string.h>
#endif

#include "tslib.hpp"

const int ALLOC_STEP = 32;

// -------------------------------------------------------------------------

static int
ALLOC_SIZE(int len)
{
   return ((len + ALLOC_STEP - 1) / ALLOC_STEP * ALLOC_STEP) + 1;
}

QString::QString()
{
   size = ALLOC_SIZE(0);
   s    = (char *) malloc(size);
   *s   = 0;
   _len = 0;
}

QString::~QString()
{
   free(s);
}

void
QString::clear()
{
   *s   = '\0';
   _len = 0;

   adjustSize();
}

QString::QString(const QString& str)
{
	size = str.size;

	s    = (char *)malloc(size);

	_len = str._len;

	memcpy(s,str.s,_len+1);
}

QString::QString(const char *str)
{
	_len = strlen(str);

	size = ALLOC_SIZE(_len);

	s    = (char *)malloc(size);

	memcpy(s,str,_len+1);
}

QString::QString(const char c,int len)
{
   size = ALLOC_SIZE(len);

   s    = (char *)malloc(size);
   _len = len;

   memset(s,c,_len);

   s[_len] = '\0';
}

void
QString::operator=(const char *x)
{
   _len = strlen(x);

   adjustSize();

   memcpy(s,x,_len+1);
}

void
QString::operator=(char x)
{
   _len = 1;

   adjustSize();

   s[0] = x;
   s[1] = '\0';
}

void
QString::operator=(const QString& str)
{
   _len = str._len;

   adjustSize();

   memcpy(s,str.s,_len+1);
}

void
QString::operator=(int i)
{
   *this = long(i);
}

void
QString::operator=(long i)
{
   *this = form("%ld",i);
}

void
QString::operator+=(const QString& str)
{
   int l = str._len;

   adjustSize(_len+l);

   memcpy(s+_len,str.s,l+1);

	_len += l;
}

void
QString::operator+=(const char *str)
{
	int l = strlen(str);

	adjustSize(_len+l);

	memcpy(s+_len,str,l+1);

	_len += l;
}

void
QString::operator+=(char c)
{
   s[_len++] = c;

   adjustSize();

   s[_len]   = '\0';
}

QString&
QString::operator<<(char c)
{
   *this += c;

   return *this;
}

QString&
QString::operator<<(const char *str)
{
   *this += str;

   return *this;
}

QString&
QString::operator<<(const QString& str)
{
   *this += str;

   return *this;
}

QString&
QString::operator<<(int i)
{
   *this << long(i);

   return *this;
}

QString&
QString::operator<<(long i)
{
   *this += form("%ld",i);

   return *this;
}

QString
operator+(const QString& s1,const QString& s2)
{
   QString tmp(s1);

   tmp += s2;

   return tmp;
}

QString
operator+(const QString& s1,const char *s2)
{
   QString tmp(s1);

   tmp += s2;

   return tmp;
}

QString
operator+(const char *s1,const QString& s2)
{
   QString tmp(s1);

   tmp += s2;

   return tmp;
}

int
QString::operator==(const char* str) const
{
  return !::stricmp(s, str);
}

int
QString::stricmp(const char* str) const
{
  return !::stricmp(s, str);
}

int
QString::operator==(const QString& str) const
{
   return !::stricmp(s,str.s);
}

int
QString::operator!=(const char *str) const
{
   return ::stricmp(s,str);
}

int
QString::operator!=(const QString& str) const
{
   return ::stricmp(s,str.s);
}

void
QString::upperCase()
{
   strupr(s);
}

void
QString::lowerCase()
{
	for(int i=0;i<_len;i++)
		s[i] = char(tolower(s[i]));
}

void
QString::del(int pos,int l)
{
   int oldlen = len();

   if(pos < _len)
   {
      char *p = s;
      int i;
      for(i=0;i<pos;i++)
         *p++ = s[i];

      if(l)
         for(i=pos+l ; s[i] && i<_len; i++)
            *p++ = s[i];

      *p = '\0';

	  _len = int(p-s);

      adjustSize();
   }
}


void
QString::insert(int pos,const char *str)
{
   int insLen = strlen(str);

   if(pos > _len)
      (*this) << QString(' ',pos-_len);

   adjustSize(_len + insLen);

   memmove(&s[pos+insLen],&s[pos],_len-pos+1);
   memcpy(&s[pos],str,insLen);

   _len += insLen;
}


QString
QString::sub(int pos,int l) const
{
   QString tmp;

   if(l == 0)
      l = _len - pos;

   for(int i=pos ; i<pos+l && i<_len; i++) tmp << s[i];

   return tmp;
}

char
QString::lastChar() const
{
   return (*s != '\0') ? s[_len-1] : '\0';
}

void
QString::delFirst(char c)
{
   if(firstChar() != '\0' && (c == '\0' || c == firstChar()))
      del(0,1);
}

void
QString::delLast(char c)
{
   if(_len > 0 && (c == '\0' || c == lastChar()))
   {
      s[--_len] = '\0';

      adjustSize();
   }
}


void
QString::ltrim()
{
	char	*orig_s = s ,
			*p      = s ;

	for( ; *p && strchr(" \n\t",*p); p++)
		_len--;

   if(s != p)
   {
      while(*p)
         *s++ = *p++;

      *s = *p;
   }

   s = orig_s;

   adjustSize();
}

void
QString::rtrim()
{
	char *p = s + _len;

	while(p-- > s)
		if(strchr(" \n\t",*p))
		{
			_len--;
			*p = '\0';
		}
	else
		break;

	adjustSize();
}

void
QString::trim()
{
   ltrim();
   rtrim();
}

void
QString::adjustSize()
{
   adjustSize(_len);
}

void
QString::adjustSize(int len)
{
   int newsize = ALLOC_SIZE(len);

   if(newsize != size)
   {
      size = newsize;
      s    = (char *) realloc(s,size);
   }
}

void
QString::mixedCase()
{
   char last = ' ';
   char *p = s;

   for(; *p ; p++)
   {
      *p = char((isalpha(last)) ? tolower(*p) : toupper(*p));

      last = *p;
   }
}


void
QString::justify(justification j , int l)
{
	int orgLen = _len;

	if(l == 0) 
		l = orgLen;

	trim();

	if(l > orgLen)
		switch(j)
			{
				case left    :
					{
						(*this) += QString(' ',l - orgLen);
					}
					break;

				case right   :
					{
						insert(0,QString(' ',l - orgLen));
					}
					break;

					case centered:
					{
						(*this) = QString(' ',(l-orgLen)/2) + s + QString(' ',l - orgLen - (l-orgLen)/2);
					}
					break;
			}
}

int
QString::replace(const char *search,const char *replace,bool sens,int maxcount)
{
   if(find(search,sens) < 0)
      return 0;

   int count = 0;
   int search_len = strlen(search);
   int l = _len - search_len + 1;
   QString result;

   int i;
   for(i = 0; i < l; i++)
   {
      if(   ( sens && !memcmp (&s[i] , search , search_len))
         || (!sens && !memicmp(&s[i] , search , search_len))
        )
      {
         result << replace;
         i += search_len - 1;

         if(++count >= maxcount && maxcount) break;
      }
      else
      {
         result << s[i];
      }
   }

   result << &s[i];

   (*this) = result;

   return count;
}


int
QString::find(const char *search,bool sens) const
{
   int search_len = strlen(search);
   int l = _len - search_len + 1;

   for(int i = 0; i < l; i++)
   {
      if(   ( sens && !memcmp (&s[i] , search , search_len))
         || (!sens && !memicmp(&s[i] , search , search_len))
        )
      {
         return i;
      }
   }

   return -1;
}

int
QString::find(char search,bool sens) const
{
   if(!isalpha(search))
      sens = true;
   else
      if(!sens)
         search = (char) toupper(search);

   int l = _len;

   for(int i = 0; i < l; i++)
   {
      if(sens)
      {
         if(s[i] == search)
            return i;
      }
      else
      {
         if(toupper(s[i]) == search)
            return i;
      }
   }

   return -1;
}

void 
QString::assignFormattedNumber(long n, char thou_sep)
{
	char *sep = ".";

	if(thou_sep)
		*sep = thou_sep;

	(*this) = n;

	if(_len > 3)
		insert(_len-3,sep);

	if(_len > 7)
		insert(_len-7,sep);

	if(_len > 11)
		insert(_len-11,sep);
}
