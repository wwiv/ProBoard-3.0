// TTYWnd.cpp : implementation file
//

#include "stdafx.h"

#include "ttywnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTTYWnd

CTTYWnd::CTTYWnd() : screen(80,25)
{
   font = new CFont;

   font->CreateFont( -20, 10, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, OEM_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH|FF_DONTCARE, "Terminal" );

   terminal.status = 0;
   terminal.needed = 0;
   terminal.par    = 0;

   colorTable[0] = RGB(0,0,0);
   colorTable[1] = RGB(0,0,127);
   colorTable[2] = RGB(0,127,0);
   colorTable[3] = RGB(0,127,127);
   colorTable[4] = RGB(127,0,0);
   colorTable[5] = RGB(127,0,127);
   colorTable[6] = RGB(127,127,0);
   colorTable[7] = RGB(127,127,127);
   colorTable[8] = RGB(0,0,0);
   colorTable[9] = RGB(0,0,255);
   colorTable[10]= RGB(0,255,0);
   colorTable[11]= RGB(0,255,255);
   colorTable[12]= RGB(255,0,0);
   colorTable[13]= RGB(255,0,255);
   colorTable[14]= RGB(255,255,0);
   colorTable[15]= RGB(255,255,255);


	LOGFONT lf;

   font->GetLogFont(&lf);

   fh = abs(lf.lfHeight);
   fw = abs(lf.lfWidth);

   curColor    = 7;
   curX = curY = 1;

   caretOwned = FALSE;

   sp = 0;

   //SetBkColor(RGB(0,0,0));
}

CTTYWnd::~CTTYWnd()
{
   delete font;
}


BEGIN_MESSAGE_MAP(CTTYWnd, CWnd)
	//{{AFX_MSG_MAP(CTTYWnd)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_MESSAGE(WM_USER_SCROLL,EvUserScroll)
	ON_MESSAGE(WM_USER_UPDATE_CURSOR,EvUserUpdateCursor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTTYWnd message handlers

void CTTYWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect(dc.m_ps.rcPaint);

//	GetClientRect(&rect);

	dc.SelectObject(*font);

   int arr[80];

   for(int i=0;i<80;i++)
      arr[i] = fw;

   int minx = rect.left   / fw;
   int maxx = rect.right  / fw;
   int miny = rect.top    / fh;
   int maxy = rect.bottom / fh;

   unsigned char prevcolor = screen.colorAt(minx,miny);

   dc.SetBkColor(colorTable[prevcolor >> 4]);
   dc.SetTextColor(colorTable[prevcolor % 16]);

   char s[80];

   for(int y=miny;y<=maxy && y <25;y++)
   {
      int  s_start = minx;
      int  s_count = 0;
      BYTE s_color = screen.colorAt(minx,y);

      for(int x=minx;x<=maxx && x < 80;x++)
      {
         BYTE c = screen.colorAt(x,y);

         if(c == s_color)
         {
            s[s_count++] = screen.charAt(x,y);
            continue;
         }

         if(prevcolor != s_color)
         {
            if((s_color >> 4) != (prevcolor >> 4))
               dc.SetBkColor(colorTable[s_color >> 4]);

            dc.SetTextColor(colorTable[s_color % 16]);

            prevcolor = s_color;
         }

         dc.ExtTextOut(s_start*fw,y*fh,ETO_OPAQUE,&CRect(s_start*fw,y*fh,(s_start+s_count)*fw,y*fh+fh),s,s_count,arr);

         s_color = c;
         s_count = 1;
         s_start = x;

         s[0] = screen.charAt(s_start,y);
      }

      if(s_count)
      {
         if(prevcolor != s_color)
         {
            if((s_color >> 4) != (prevcolor >> 4))
               dc.SetBkColor(colorTable[s_color >> 4]);

            dc.SetTextColor (colorTable[s_color % 16]);

            prevcolor = s_color;
         }

         dc.ExtTextOut(s_start*fw,y*fh,ETO_OPAQUE,&CRect(s_start*fw,y*fh,(s_start+s_count)*fw,y*fh+fh),s,s_count,arr);
      }
   }




	// TODO: Add your message handler code here

	// Do not call CWnd::OnPaint() for painting messages
}

void CTTYWnd::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	CreateSolidCaret(fw, fh/4);

	ShowCaret();

   caretOwned = TRUE;

   placeCursor();
}

void CTTYWnd::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

   caretOwned = FALSE;

   HideCaret();
   DestroyCaret();
}

#define TERMINAL_NORMAL          0
#define TERMINAL_ANSI            1
#define TERMINAL_AVT_REPCHAR     2
#define TERMINAL_AVT             3
#define TERMINAL_AVT_ATTR        4
#define TERMINAL_AVT_MOVE        5
#define TERMINAL_AVT_RLE         6

static
 struct clr
   {
   int val;
   BYTE andval;
   BYTE orval;
   } colors[]=
      {
       {  0 , 0x00 , 0x07 },
       {  1 , 0xFF , 0x08 },
       {  5 , 0xFF , 0x80 },
       {  6 , 0xFF , 0x80 },
       { 30 , 0xF8 , 0x00 },
       { 31 , 0xF8 , 0x04 },
       { 32 , 0xF8 , 0x02 },
       { 33 , 0xF8 , 0x06 },
       { 34 , 0xF8 , 0x01 },
       { 35 , 0xF8 , 0x05 },
       { 36 , 0xF8 , 0x03 },
       { 37 , 0xF8 , 0x07 },
       { 40 , 0x8F , 0x00 },
       { 41 , 0x8F , 0x40 },
       { 42 , 0x8F , 0x20 },
       { 43 , 0x8F , 0x60 },
       { 44 , 0x8F , 0x10 },
       { 45 , 0x8F , 0x50 },
       { 46 , 0x8F , 0x30 },
       { 47 , 0x8F , 0x70 }
      };

CTTYWnd&
CTTYWnd::operator<<(char c)
{
   int i;

   switch(terminal.status)
   {
      case TERMINAL_NORMAL:
         {
            switch(c)
               {
                 case  0 : break;
         /*^Y*/  case 25 : terminal.status = TERMINAL_AVT_REPCHAR;
			   terminal.needed = 2;
                           break;
         /*LF*/  case 10 : curX = 1;
                           curY++;
                           break;
         /*CR*/  case 13 : curX = 1;
                           break;
         /*FF*/  case 12 : curColor = 7;
                           clear();
                           break;
         /*BEL*/ case  7 : // Do beep here
                           break;
         /*BS*/  case  8 : if(curX>1) curX--;
                           screen.charAt(curX-1,curY-1) = ' ';
                           screen.colorAt(curX-1,curY-1) = curColor;
                           invalidate(curX,curY,curX,curY);
                           break;
         /*ESC*/ case 27 : terminal.status = TERMINAL_ANSI;
                           terminal.par  = 0;
                           terminal.p[0] = terminal.p[1]
					  = terminal.p[2]
                                          = terminal.p[3] = 0;
                           break;
         /*^V*/  case 22 : terminal.status = TERMINAL_AVT;
                           break;
                 default : screen.charAt (curX-1,curY-1) = c;
			                  screen.colorAt(curX-1,curY-1) = curColor;

                           invalidate(curX,curY,curX,curY);
                           //UpdateWindow();

                           curX++;
                           break;
	       }
         }
         break; // case TERMINAL_NORMAL

      case TERMINAL_ANSI:
         {
            if(isalpha(c))
            {
               terminal.status = TERMINAL_NORMAL;
               terminal.par++;

               switch(c)
               {
                  case 'f': // Goto row,col
                  case 'H':
                     {
                        if(!terminal.p[0]) terminal.p[0]++;
                        if(!terminal.p[1]) terminal.p[1]++;

                        setPos( terminal.p[1] , terminal.p[0] );
                     }
                     break;

                  case 'A': // Cursor Up
                     {
                        if(!terminal.p[0])
                           terminal.p[0]++;

                        cursorUp(terminal.p[0]);
                     }
                     break;

                  case 'B': // Cursor Down
                     {
                        if(!terminal.p[0])
                           terminal.p[0]++;

                        cursorDown(terminal.p[0]);
                     }
                     break;

                  case 'C': // Cursor Right
                     {
                        if(!terminal.p[0])
                           terminal.p[0]++;

                        cursorRight(terminal.p[0]);
                     }
                     break;

                  case 'D': // Cursor Left
                     {
                        if(!terminal.p[0])
                           terminal.p[0]++;

                        cursorLeft(terminal.p[0]);
                     }
                     break;

                  case 's': // Save Cursor Position
                     {
                        saveCursor();
                     }
                     break;

                  case 'u': // Restore Cursor Position
                     {
                        restoreCursor();
                     }
                     break;

                  case 'J': // Clear Screen
                     {
                        if(terminal.p[0] == 2)
                           clear();
                     }
                     break;

                  case 'K': // Clear EOL
                     {
                        for(i=curX ; i<=80 ;i++)
                        {
                           screen.charAt(i-1,curY-1) = ' ';
                           screen.colorAt(i-1,curY-1) = curColor;
                        }
                     }
                     break;

                  case 'm': // Set Color
                     {
                        for(i=0 ; i<terminal.par ; i++)
                        {
                           for(int j=0;j<20;j++)
                              if(colors[j].val==terminal.p[i])
                              {
                                 curColor &= colors[j].andval;
                                 curColor |= colors[j].orval;
                                 break;
                              }
                        }
                     }
                     break;
               }
            }
            else
            {
               if(isdigit(c))
               {
                  terminal.p[terminal.par] *= 10;
                  terminal.p[terminal.par] += c-'0';
               }
               else
               {
                  if(c==';')
                  {
                     terminal.p[++terminal.par] = 0;
                  }
                  else
                  {
                     if(c!='[')
                        terminal.status = TERMINAL_NORMAL;
                  }
               }
            }
         }
         break; // case TERMINAL_ANSI

      case TERMINAL_AVT_REPCHAR:
         {
            if(terminal.needed == 1)
            {
               terminal.status = TERMINAL_NORMAL;

               for(i=0;i<int(BYTE(c));i++)
                  (*this) << BYTE(terminal.p[0]);
            }
            else
            {
               terminal.p[0] = c;
               terminal.needed--;
            }
         }
         break;

      case TERMINAL_AVT:
         {
            switch(c)
               {
                  case 1: // Go in Attribute Set Mode
                     {
                        terminal.status = TERMINAL_AVT_ATTR;
                     }
                     break;

                  case 2: // Set Blink On
                     {
                        curColor |= 0x80;

                        terminal.status = TERMINAL_NORMAL;
                     }
                     break;

                  case 3: // Cursor Up
                     {
                        cursorUp();

                        terminal.status = TERMINAL_NORMAL;
                     }
                     break;

                  case 4: // Cursor Down
                     {
                        cursorDown();

                        terminal.status = TERMINAL_NORMAL;
                     }
                     break;

                  case 5: // Cursor Left
                     {
                        cursorLeft();

                        terminal.status = TERMINAL_NORMAL;
                     }
                     break;

                  case 6: // Cursor Right
                     {
                        cursorRight();

                        terminal.status = TERMINAL_NORMAL;
                     }
                     break;

                  case 7: // Clear EOL
                     {
                        for(i=curX ; i<=80 ; i++)
                        {
                           screen.charAt(i-1,curY-1) = ' ';
                           screen.colorAt(i-1,curY-1) = curColor;
                        }

                        terminal.status = TERMINAL_NORMAL;
                     }
                     break;

                  case 8: // Start Move Cursor Command
                     {
                        terminal.status = TERMINAL_AVT_MOVE;

                        terminal.needed = 2;
                     }
                     break;

                  case 25: // Start RLE command
                     {
                        terminal.status = TERMINAL_AVT_RLE;
                        terminal.needed = 0;
                     }
                     break;

                  default: // Unknown command
                     {
                        terminal.status = TERMINAL_NORMAL;
                        (*this) << c;
                     }
                     break;
               }
         }
         break;

      case TERMINAL_AVT_ATTR:
         {
            curColor = BYTE(c);

            terminal.status = TERMINAL_NORMAL;
         }
         break;

      case TERMINAL_AVT_MOVE:
         {
            if(terminal.needed==1)
            {
               if(c<=80 && c>=1 && terminal.p[0]>=1 && terminal.p[0]<=25)
               {
                  curX = c;
                  curY = terminal.p[0];
               }
               else
               {
                  terminal.status = TERMINAL_NORMAL;

                  (*this) << char(terminal.p[0]) << c;
               }

               terminal.status = TERMINAL_NORMAL;
            }
            else
            {
               terminal.p[0] = c;
               terminal.needed--;
            }
         }
         break;

      case TERMINAL_AVT_RLE:
         {
            if(!terminal.needed)
            {
               terminal.p[0]     = BYTE(c);
               terminal.rle_buf  = new BYTE[c];
               terminal.par      = 0;
               terminal.needed   = BYTE(c+1);
            }
            else
            {
	       if(terminal.needed>1)
               {
                  terminal.rle_buf[terminal.par++] = c;
                  terminal.needed--;
               }
               else
               {
                  terminal.status = TERMINAL_NORMAL;

                  int repcount = terminal.p[0];
                  BYTE *buf=new BYTE[repcount];

                  for(i=0;i<repcount;i++) buf[i]=terminal.rle_buf[i];

                  delete [] terminal.rle_buf;

                  for(i=0;i<c;i++)
                     for(int j=0;j<repcount;j++)
                        (*this) << buf[j];
               }
            }
         }
         break;
   }


   if(curX > 80)
   {
      curX = 1;
      curY++;
   }

   if(curY > 25)
   {
      scroll();
      curY = 25;
   }

   return *this;
}


void
CTTYWnd::setPos(int x,int y)
{
   curX = x;
   curY = y;
}

void
CTTYWnd::cursorUp(int n)
{
   curY -= n;

   updateCursor();
}

void
CTTYWnd::cursorDown(int n)
{
   curY += n;

   updateCursor();
}

void
CTTYWnd::cursorLeft(int n)
{
   curX -= n;

   updateCursor();
}

void
CTTYWnd::cursorRight(int n)
{
   curX += n;

   updateCursor();
}

void
CTTYWnd::updateCursor()
{
   if(curX < 1)
      curX = 1;
   if(curX > 80)
      curX = 80;
   if(curY < 1)
      curY = 1;
   if(curY > 25)
      curY = 25;

   if(caretOwned && !noCursorUpdate)
   {
      int x = fw*(curX-1);
      int y = fh*curY-fh/4;

      SetCaretPos(CPoint(x,y));
   }
}

void
CTTYWnd::scroll(BYTE direction,int numlines)
{
   SendMessage(WM_USER_SCROLL,direction,numlines);
}


void
CTTYWnd::saveCursor()
{
   if(sp < 5)
   {
      oldX[sp] = curX;
      oldY[sp] = curY;

      sp++;
   }
}

void
CTTYWnd::restoreCursor()
{
   if(sp > 0)
   {
      sp--;

      setPos(oldX[sp],oldY[sp]);
   }
}

void
CTTYWnd::placeCursor()
{
   bool old = noCursorUpdate;

   noCursorUpdate = FALSE;

   updateCursor();

   noCursorUpdate = old;
}



void
CTTYWnd::invalidate(int x1,int y1,int x2,int y2)
{
   CRect rect((x1-1)*fw,(y1-1)*fh,x2*fw,y2*fh);

   InvalidateRect(rect);
}

LRESULT
CTTYWnd::EvUserUpdateCursor(WPARAM,LPARAM)
{
   placeCursor();

   return 1;
}

LRESULT
CTTYWnd::EvUserScroll(WPARAM direction,LPARAM numlines)
{
   int dy = fh * numlines * (direction ? 1:-1);
   CRect   rec(0,0,80*fw-1,25*fh-1);

   if(!direction)
      screen.scrollUp(numlines);
   else
      screen.scrollDown(numlines);

   if(caretOwned)
      HideCaret();

   ScrollWindowEx(0,dy,&rec,&rec,0,0,SW_INVALIDATE);

   UpdateWindow();

   if(caretOwned)
      ShowCaret();

   return 1;
}



void CTTYWnd::GetDimensions(CRect& rect)
{
   rect.left = 0;
   rect.top = 0;

   rect.right = fw * 80 - 1;
   rect.bottom = fh * 25 - 1;
}


void 
CTTYWnd::setFont(LOGFONT& lf)
{
   delete font;

   font = new CFont;

   font->CreateFontIndirect(&lf);

   CClientDC dc(this);

   dc.SelectObject(*font);

   dc.GetCharWidth('M','M',&fw);

   fh = abs(lf.lfHeight);

   if(caretOwned)
   {
      HideCaret();
      DestroyCaret();
 	   CreateSolidCaret(fw, fh/4);
	   ShowCaret();

      placeCursor();
   }
}

void 
CTTYWnd::getFont(LOGFONT& lf)
{
   font->GetLogFont(&lf);
}
