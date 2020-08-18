// PBWnd.cpp : implementation file
//

#include "stdafx.h"

#include <compplib.hpp>

#include "ttywnd.h"
#include "pbthread.h"
#include "PBWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPBWnd

CPBWnd::CPBWnd(CSerial *_comlink) : serial(_comlink)
{
   mainThread = NULL;
}


CPBWnd::~CPBWnd()
{
   if(mainThread)
   {
      mainThread->TerminateAndWait();

      delete mainThread;
   }
}


BEGIN_MESSAGE_MAP(CPBWnd, CTTYWnd)
	//{{AFX_MSG_MAP(CPBWnd)
	ON_WM_CREATE()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPBWnd message handlers

int CPBWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTTYWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

   mainThread = new CPBThread(this,serial);
   
   mainThread->Start();

	return 0;
}

void CPBWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

   mainThread->keyPressed(nChar,nRepCnt);
	
	CTTYWnd::OnChar(nChar, nRepCnt, nFlags);
}
