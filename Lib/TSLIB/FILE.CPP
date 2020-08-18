#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <sys/stat.h>
#include <errno.h>
#include <assert.h>
#include <sys/locking.h>

#include "tslib.hpp"

const BYTE action_none  = 0;
const BYTE action_read  = 1;
const BYTE action_write = 2;
const BYTE action_seek  = 3;

const BYTE buf_none  = 0;
const BYTE buf_read  = 1;
const BYTE buf_write = 2;

static int
calc_oflags(WORD mode)
{
   int oflags = O_BINARY;

   switch(mode & 3)
   {
      case fmode_read : oflags |= O_RDONLY;
                        break;
      case fmode_write: oflags |= O_WRONLY;
                        break;
      case fmode_rw   : oflags |= O_RDWR;
                        break;
   }

   return oflags;
}

void
QFile::init()
{
   fh         = -1;
   buffer     = NULL;
   bufPtr     = NULL;
   bufSize    = 0;
   bytesInBuf = 0;
   bufPos     = 0;
   bufType    = buf_none;
   mode       = 0;
   atEof      = false;
   lastAction = action_none;
}

QFile::QFile(const char *fname,WORD m,WORD bufsize)
{
   init();
   clearError();
   open(fname,m,bufsize);
}

bool
QFile::open(const char *fname,WORD m,WORD buf)
{
   if(fh>0) return false;

   init();
   clearError();

   mode = m;

   if(!(mode & 0x70)) mode |= fmode_shared;

   int oflags = calc_oflags(mode);
   int shflags = 0;

   switch(mode & 0x70)
   {
      case fmode_excl   : shflags = SH_DENYRW;
                          break;
      case fmode_denyrd : shflags = SH_DENYRD;
                          break;
      case fmode_denywr : shflags = SH_DENYWR;
                          break;
      case fmode_shared : shflags = SH_DENYNO;
                          break;
   }


   if(mode & fmode_create)
   {
      if( (mode & 3) == fmode_read )
      {
         mode &= ~fmode_read;
         mode |= fmode_write;
      }

      mode &= ~fmode_create;
      mode |= fmode_copen;

      oflags = calc_oflags(mode);
   }
   else
   {
      time_t t = time(NULL);

      while(time(NULL)-t < (time_t)10)
      {
         fh = ::sopen(fname,oflags,shflags);

         if(fh>0 || errno != EACCES) break;

         sleep_clock();
      }
   }

   if(fh<0 && (mode & fmode_copen))
   {
      fh = ::sopen(fname,oflags|O_CREAT|O_TRUNC,shflags,S_IREAD|S_IWRITE);

      if(fh<0)
      {
         errorCode = errno;

         return false;
      }
   }

   if(fh<0)
   {
      errorCode = errno;

      return false;
   }

   if(textMode() && !buf) buf = 512;

   if(buf)
   {
      buffer = new BYTE[buf];

      if(buffer != NULL)
      {
         bufPtr     = buffer;
         bufSize    = buf;
         mode      |= fmode_buffered;
      }
   }

   if(mode & fmode_append) seek(len());

   return bool(error()==0);
}

void
QFile::close()
{
   if(fh < 0) return;

   if(buffered())
   {
      flush();
      delete [] buffer;
   }

   ::close(fh);

   init();

   clearError();
}

bool
QFile::eof() const
{
   if(buffered() && bufType == buf_read)
   {
      return bool(!!(atEof && bufPtr >= (buffer + bytesInBuf)));
   }
   else
   {
      return atEof;
   }
}


void
QFile::flush()
{
   if(!opened()) return;

   clearError();

   if(!buffered())
   {
      seek(pos());

      clearError();

      return;
   }

   if(bufType == buf_write && bytesInBuf)
   {
      lseek(fh,bufPos,SEEK_SET);

      if(WORD(::write(fh,buffer,bytesInBuf)) != bytesInBuf)
         errorCode = errno;

      lastAction = action_write;

      bufPos += bytesInBuf;
   }
   else
   {
      if(bufType == buf_read)
         bufPos += WORD(bufPtr-buffer);
   }

   lseek(fh,bufPos,SEEK_SET);

   lastAction = action_seek;

   bufPtr     = buffer;
   bytesInBuf = 0;
   bufType    = buf_none;
}

bool
QFile::fillBuffer()
{
   assert(bufType != buf_write);

   bufPos += bytesInBuf;

   bytesInBuf = 0;

   int r = ::read(fh,buffer,bufSize);

   lastAction = action_read;

   if(r < 0)
      errorCode = errno;
   else
      bytesInBuf = WORD(r);

   if(!error() && bytesInBuf<1) atEof = true;

   bufPtr = buffer;

   bufType = buf_read;

   return bool(bytesInBuf && !error());
}

unsigned
QFile::read(void *p,unsigned size)
{
   BYTE *bp = (BYTE *)p;

   if(!opened()) return 0;

   if(bufType == buf_write)
      flush();

   if(textMode())
   {
      for(unsigned i=0;i<size;i++)
      {
         int c = readByte();

         if(c < 0) break;

		 BYTE *bp = (BYTE *)p;

         *bp++ = BYTE(c);
      }

      return i;
   }

   if(!buffered())
   {
      size = ::read(fh,p,size);

      lastAction = action_read;

      if(int(size) < 0)
         errorCode = errno;
      else
         clearError();

      return error() ? 0 : size;
   }

   if(!bytesInBuf)
      if(!fillBuffer())
         return 0;

   if(bufPtr+size <= buffer+bytesInBuf)
   {
      memcpy(p,bufPtr,size);
      bufPtr += size;
      return size;
   }

   unsigned left = size;

   while(left)
   {
      unsigned x = bytesInBuf - unsigned(bufPtr-buffer);

      if(!x)
      {
         if(!fillBuffer())
            return (size-left);
         else
            continue;
      }

      if(x >= left)
      {
         memcpy(p,bufPtr,left);
         bufPtr += left;
         return size;
      }
      else
      {
         memcpy(p,bufPtr,x);
      }

	  BYTE *bp = (BYTE *)p;

      left      -= x;
      bp        += x;
      bufPtr    += x;

	  p = (void *)bp;
   }

   return size;
}

int
QFile::readByte()
{
   if(fh<0) return -1;

   if(bufType == buf_write)
      flush();

   if(!buffered())
   {
      BYTE c;

      int n = ::read(fh,&c,1);

      lastAction = action_read;

      if(n < 0)
         errorCode = errno;

      if(n == 1)
         return int(c);

      if(n == 0)
         atEof = true;

      return -1;
   }

   for(;;)
   {
      if(bufPtr+1 > buffer+bytesInBuf || !bytesInBuf)
         if(!fillBuffer())
            return -1;

      BYTE c = *bufPtr++;

      if(c=='\r' && textMode()) continue;       // CR

      if(c==26 && textMode())
      {
         atEof = true;

         return -1;        // EOF!
      }

      return int(c);
   }
}

unsigned
QFile::write(const void *p,unsigned size)
{
   if(fh<0) return 0;

   if(textMode())
   {

	  BYTE *bp = (BYTE *)p;

      for(unsigned i=0;i<size;i++)
         if(!writeByte(*bp++)) break;

      return i;
   }

   if(bufType == buf_read)
      flush();

   if(!size)
   {
      flush();

      if(!error())
      {
          if(::_chsize(fh,pos()) < 0)
            errorCode = errno;

         lastAction = action_write;
      }

      seek(pos());

      return 0;
   }

   if(!buffered())
   {
      unsigned sizewritten = ::write(fh,p,size);

      lastAction = action_write;

      if(sizewritten != size)
         errorCode = errno;

      size = sizewritten;

      return error() ? 0 : size;
   }

   if(size>bufSize)
   {
      flush();

      unsigned sizewritten = ::write(fh,p,size);

      lastAction = action_write;

      if(sizewritten != size)
         errorCode = errno;

      size = sizewritten;

      if(error()) return 0;

      seek(bufPos + size);

      return size;
   }

   if(bufSize-size < bytesInBuf) flush();

   bufType = buf_write;

   memcpy(bufPtr,p,size);

   bufPtr     += size;
   bytesInBuf += size;

   return error() ? 0 : size;
}

bool
QFile::writeByte(BYTE c)
{
   if(fh<0) return false;

   if(bufType == buf_read)
      flush();

   if(c=='\n' && textMode())
      if(!writeByte('\r'))
         return false;

   if(!buffered())
   {
      if(::write(fh,&c,1) != 1)
         errorCode = errno;

      lastAction = action_write;
   }
   else
   {
	  if(bytesInBuf == bufSize)
         flush();

      bufType = buf_write;

      *bufPtr++ = c;
      bytesInBuf++;
   }

   return bool(!error());
}

long
QFile::seek(long p,int mode)
{
   if(fh<0) return 0;

   if(buffered() && bufType == buf_read)
   {
      if(mode == seek_cur)
      {
         p   += pos();
         mode = seek_set;
      }

      if(mode == seek_set && p>=bufPos && p<bufPos+bytesInBuf)
      {
         bufPtr = buffer + unsigned(p-bufPos);

         return p;
      }
   }

   int seek_mode = 0;

   switch(mode)
   {
      case seek_set: seek_mode = SEEK_SET;
                     break;
      case seek_cur: seek_mode = SEEK_CUR;
                     break;
      case seek_end: seek_mode = SEEK_END;
                     break;
   }

   if(!buffered())
   {
      p = lseek(fh,p,seek_mode);

      lastAction = action_seek;

      if(p < 0)
         errorCode = errno;

      return error() ? -1L : p;
   }

   flush();

   bufPos = lseek(fh,p,seek_mode);

   lastAction = action_seek;

   if(bufPos < 0)
      errorCode = errno;

   return error() ? -1L : bufPos;
}

long
QFile::pos()
{
   if(fh<0) return 0;

   if(error()) return -1;

   long p;

   if(buffered())
   {
      p = bufPos + WORD(bufPtr-buffer);
   }
   else
   {
      p = lseek(fh,0,SEEK_CUR);

      lastAction = action_seek;

      if(p < 0)
         errorCode = errno;
   }

   return error() ? -1L : p;
}

bool
QFile::lock(long pos,long len)
{
   if(fh < 0) return false;

   flush();

   time_t t = time(NULL);

   while((time(NULL)-t)<20)
   {
      errno = 0;

	  lseek(fh,pos,SEEK_SET);

      if(!_locking(fh,_LK_NBLCK,len)) break;

      if(errno != EACCES) break;

      sleep_clock();
   }

   errorCode = errno;

   return bool(!error());
}

bool
QFile::unlock(long pos,long len)
{
   if(fh < 0) return false;

   flush();

   time_t t = time(NULL);

   while((time(NULL)-t)<20)
   {
      errno = 0;

	  lseek(fh,pos,SEEK_SET);

      if(!_locking(fh,_LK_UNLCK,len)) break;

      if(errno != EACCES) break;

      sleep_clock();
   }

   errorCode = errno;

   return bool(!error());
}

void
QFile::cut()
{
   BYTE dummy;

   write(&dummy,0);
}

long
QFile::len()
{
   if(fh<0) return 0;

   long p = pos();
   long l = seek(0,seek_end);

   seek(p);

   return l;
}

void
QFile::enableBuffer()
{
   if(fh<0) return;

   if(buffered()) flush();

   if(bufSize) mode |= fmode_buffered;
}

void
QFile::disableBuffer()
{
   if(fh<0) return;

   if(buffered())
   {
      flush();
      mode ^= fmode_buffered;
   }
}

QFile&
QFile::operator<<(char c)
{
   write(&c,1);

   return *this;
}

QFile&
QFile::operator<<(int i)
{
   write(&i,sizeof(i));

   return *this;
}

QFile&
QFile::operator<<(WORD w)
{
   write(&w,sizeof(w));

   return *this;
}

QFile&
QFile::operator<<(long l)
{
   write(&l,sizeof(l));

   return *this;
}

QFile&
QFile::operator<<(DWORD d)
{
   write(&d,sizeof(d));

   return *this;
}

QFile&
QFile::operator<<(const char *s)
{
   write(s,strlen(s));

   return *this;
}

QFile&
QFile::operator>>(char& c)
{
   read(&c,1);

   return *this;
}

QFile&
QFile::operator>>(int& i)
{
   read(&i,2);

   return *this;
}

QFile&
QFile::operator>>(WORD& i)
{
   read(&i,2);

   return *this;
}

QFile&
QFile::operator>>(long& i)
{
   read(&i,4);

   return *this;
}

QFile&
QFile::operator>>(DWORD& i)
{
   read(&i,4);

   return *this;
}

bool
QFile::readLine(char *s,int max)
{
   if(!textMode()) return false;

   for(int i=0;i<max;)
   {
      int c = readByte();

      if(c < 0) break;

      *s++ = char(c);
      i++;

      if(char(c) == '\n') break;
   }

   *s   = '\0';

   return bool(!!i);
}

QString
QFile::readLine()
{
	if(!textMode()) return "";

	QString s;

	char tmp_buf[200];
	int i=0;

	for(;;)
	{
		int c = readByte();

		if(c < 0) break;

		tmp_buf[i++] = char(c);

		if(i==199 || char(c)=='\n')
		{
			tmp_buf[i]=0;
			s += tmp_buf;
			i=0;

			if(char(c) == '\n') break;
		}
   }

   tmp_buf[i] = 0;
   s += tmp_buf;

   return s;
}


bool
QFile::printf(const char *fmt,...)
{
   bool ret = true;
   va_list x;
   va_start(x,fmt);

   char *s = new char[ strlen(fmt) + 1024 ];

   int l = vsprintf(s,fmt,x);

   if(write(s,l) != unsigned(l)) ret = false;

   delete s;
   return ret;
}
