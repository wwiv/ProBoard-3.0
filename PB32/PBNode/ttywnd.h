#ifndef __TTYWND_H
#define __TTYWND_H

#include "SCRNBUF.HPP"

// TTYWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTTYWnd window

#define WM_USER_SCROLL (WM_USER+1)
#define WM_USER_UPDATE_CURSOR (WM_USER+2)
#define WM_USER_CHANGE_FONT (WM_USER+3)

class CTTYWnd : public CWnd
{
	protected:
      CFont *font;
		int fw;
		int fh;
	private:
		CScreenBuffer screen;
		COLORREF colorTable[16];

		BYTE curColor;
		int curX,curY;
		int oldX[5],oldY[5];
		int sp;
		bool noCursorUpdate;

		bool caretOwned;

		struct 
			{
				BYTE status;
				BYTE needed;
				int  p[5];
				int  par;
				BYTE *rle_buf;
			} terminal;

      void updateCursor();
      void invalidate(int x1,int y1,int x2,int y2);

   public:
	void GetDimensions(CRect& rect);
      void scroll(BYTE direction = 0,int numlines=1);

      BYTE attrib()
         {
            return curColor;
         }
      void attrib(BYTE a)
         {
            curColor = a;
         }
      void clear()
         {
            screen.clear();
            Invalidate();
            setPos(1,1);
         }

      void getPos(int& x,int& y) { x=curX ; y=curY; }

      void setPos(int x,int y);

      void cursorUp   (int n = 1);
      void cursorDown (int n = 1);
      void cursorLeft (int n = 1);
      void cursorRight(int n = 1);
      void saveCursor();
      void restoreCursor();
      void disableCursor()
	      {
            noCursorUpdate = TRUE;
	      }
      void enableCursor()
	      {
	         noCursorUpdate = FALSE;
	         updateCursor();
	      }
      void placeCursor();

      CTTYWnd& operator<<(char c);

      LRESULT EvUserUpdateCursor(WPARAM,LPARAM);
      LRESULT EvUserScroll(WPARAM,LPARAM);
      LRESULT EvUserChangeFont(WPARAM,LPARAM);

      void setFont(LOGFONT&);
      void getFont(LOGFONT&);


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTYWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	CTTYWnd();
	virtual ~CTTYWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTTYWnd)
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
