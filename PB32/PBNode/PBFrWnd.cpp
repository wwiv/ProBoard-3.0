// PBFrWnd.cpp : implementation file
//

#include "stdafx.h"

#include "PBNode.h"
#include "PBFrWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPBFrameWnd

//IMPLEMENT_DYNCREATE(CPBFrameWnd, CFrameWnd)

CPBFrameWnd::CPBFrameWnd(CSerial *comlink)
   : wndClient(comlink)
{
   aboutbox = NULL;
}


CPBFrameWnd::~CPBFrameWnd()
{
   if(aboutbox)
   {
      aboutbox->DestroyWindow();
      delete aboutbox;
   }
}


BEGIN_MESSAGE_MAP(CPBFrameWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CPBFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(IDM_HANGUP, OnHangup)
	ON_COMMAND(IDM_MINIMIZE, OnMinimize)
	ON_COMMAND(IDM_INFRONT, OnInfront)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_COMMAND(IDM_FONT, OnFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPBFrameWnd message handlers

int CPBFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
   CRect rect;

   GetClientRect(&rect);

   wndClient.Create(NULL,"",WS_CHILD|WS_VISIBLE|WS_MAXIMIZE,rect,this,1);
	
   wndClient.GetDimensions(rect);

   AdjustWindowRectEx(&rect,  GetStyle(), TRUE, GetExStyle());

   rect.OffsetRect(50,50);

   MoveWindow(&rect);

   CenterWindow();

	return 0;
}

void CPBFrameWnd::OnSetFocus(CWnd* pOldWnd) 
{
	CFrameWnd::OnSetFocus(pOldWnd);
	
   wndClient.SetFocus();
}

void CPBFrameWnd::OnHangup() 
{
   PostMessage(WM_CLOSE);
}

void CPBFrameWnd::OnMinimize() 
{
   ShowWindow(SW_MINIMIZE);
}

void CPBFrameWnd::OnInfront() 
{
   SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
}

void CPBFrameWnd::OnAbout() 
{
   if(aboutbox)
   {
      aboutbox->ShowWindow(SW_SHOW);
      aboutbox->SetActiveWindow();        
   }
   else
   {
      aboutbox = new CDialog;
      aboutbox->Create(IDD_ABOUTBOX,this);
   }
}

void CPBFrameWnd::OnFont() 
{
   LOGFONT lf;

   wndClient.getFont(lf);

   CFontDialog dlg(&lf,CF_FIXEDPITCHONLY|CF_SCREENFONTS,NULL,this);

   if(dlg.DoModal() == IDOK)
   {
      lf = dlg.m_lf;

      wndClient.setFont(lf);

      CRect rect;


      wndClient.GetWindowRect(&rect);

      int ofx = rect.left;
      int ofy = rect.top;

      wndClient.GetDimensions(rect);

      AdjustWindowRectEx(&rect,  GetStyle(), TRUE, GetExStyle());

      rect.OffsetRect(ofx - rect.left,ofy - rect.top);

      MoveWindow(&rect);
   }
}

