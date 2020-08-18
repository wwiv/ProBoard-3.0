/***************************************************************************
 class QDirScan

 Compatibility: DOS, OS/2, Windows
 Models       : 16 bit - 32 bit
***************************************************************************/

#include <stdio.h>
#include <direct.h>
#include <io.h>

#define BYTE _BYTE

#include "tslib.hpp"

#undef BYTE

extern "C" 
	{
		#include "dirport.h"
	}

#define BYTE _BYTE

QDirScan::QDirScan()
{
   handle = -1;
   ok   = 0;
   data = (void *) new DOSFileData;
}


QDirScan::QDirScan(const char *wildcard)
{
   handle = -1;
   ok   = 0;
   data = (void *)new DOSFileData;

   first(wildcard);
}

QDirScan::QDirScan(const char *wildcard, int attr)
{
   handle = -1;
   ok   = 0;
   data = (void *)new DOSFileData;

   first(wildcard,attr);
}

QDirScan::~QDirScan()
{
	if(handle >= 0)
		FIND_END((DOSFileData *)data);

   delete ((DOSFileData *)data);
}

int
QDirScan::first(const char *wildcard)
{
	if(handle >= 0)
		FIND_END((DOSFileData *)data);

   int success = FIND_FIRST((char *)wildcard,_A_NORMAL,(DOSFileData *)data);

   handle = 1;

   ok = !success;

   return ok;
}

int
QDirScan::first(const char *wildcard,int attr)
{
	if(handle >= 0)
		FIND_END((DOSFileData *)data);

   int success = FIND_FIRST((char *)wildcard,attr,(DOSFileData *)data);

   handle = 1;

   ok = !success;

   return ok;
}



int
QDirScan::next()
{
   return (ok = !FIND_NEXT((DOSFileData *)data));
}

char *
QDirScan::name() const
{
   return ff_name((DOSFileData *)data);
}

long
QDirScan::size() const
{
   return ff_size((DOSFileData *)data);
}

int
QDirScan::flags() const
{
   return ff_attr((DOSFileData *)data);
}

QDate
QDirScan::date() const
{
   QDate d;

   d.set(   ff_day((DOSFileData *)data),
            ff_mo((DOSFileData *)data),
            ff_yr((DOSFileData *)data)
        );

   return d;
}

QTime
QDirScan::time() const
{
   QTime t;

   t.set(  ff_hr((DOSFileData *)data),
           ff_min((DOSFileData *)data),
           ff_tsec((DOSFileData *)data) * 2
        );

   return t;
}
