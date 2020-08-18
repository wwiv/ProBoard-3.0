#include "stdafx.h"

#include <string.h>
#include "scrnbuf.hpp"

CScreenBuffer::CScreenBuffer(int cols,int rows)
{
   maxCols = cols;
   maxRows = rows;

   buf  = new unsigned char[maxRows * maxCols * 2];

   clear();
}

CScreenBuffer::~CScreenBuffer()
{
   delete [] buf;
}

void
CScreenBuffer::clear(unsigned char color)
{
   for(int i=0;i<maxCols * maxRows;i++)
   {
      buf[i*2  ] = ' ';
      buf[i*2+1] = color;
   }
}

void
CScreenBuffer::scrollUp(int nlines,unsigned char attr)
{
   memmove(buf,&buf[maxCols*nlines*2],maxCols*maxRows*2-nlines*maxCols*2);

   unsigned char *p = &buf[(maxRows-nlines)*maxCols*2];

   for(int i=0;i<nlines*maxCols;i++)
   {
      p[i*2] = ' ';
      p[i*2+1] = attr;
   }
}

void
CScreenBuffer::scrollDown(int nlines,unsigned char/* attr*/)
{
   memmove(&buf[maxCols*nlines*2],buf,maxCols*maxRows*2-nlines*maxCols*2);
}


