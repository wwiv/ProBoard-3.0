#ifndef __SCRNBUF_HPP
#define __SCRNBUF_HPP

class CScreenBuffer
	{
      unsigned char *buf;
      int maxCols;
      int maxRows;
   public:
      CScreenBuffer(int cols,int rows);
      ~CScreenBuffer();

      unsigned char& charAt(int x,int y)  { return buf[(x+y*maxCols)*2  ]; }
      unsigned char& colorAt(int x,int y) { return buf[(x+y*maxCols)*2+1]; }

      void clear(unsigned char color=0x7);

      void scrollUp  (int nlines = 1,unsigned char attr=7);
      void scrollDown(int nlines = 1,unsigned char attr=7);
   };

#endif