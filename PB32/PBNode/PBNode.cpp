// PBNode.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PBNode.h"
#include "pbfrwnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPBNodeApp

BEGIN_MESSAGE_MAP(CPBNodeApp, CWinApp)
	//{{AFX_MSG_MAP(CPBNodeApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPBNodeApp construction

CPBNodeApp::CPBNodeApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPBNodeApp object

CPBNodeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPBNodeApp initialization

BOOL CPBNodeApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


   CSerial *serial = NULL;

   CString title;

   title = "Local Session";

   if(m_lpCmdLine[0] != '\0')
   {
      if(!strnicmp(m_lpCmdLine,"/T=",3))
      {
         DWORD n = strtoul(&m_lpCmdLine[3],NULL,16);

         if(n)
         {
            serial = new CSerial((SOCKET)n);

            title = serial->IPName();
         }
      }

      if(!strnicmp(m_lpCmdLine,"/S=",3))
      {
         int port  = atoi(&m_lpCmdLine[3]);
         long baud = atol(&m_lpCmdLine[5]);
         
         if(baud && port)
         {
            serial = new CSerial(port,baud);

            title = CString("Serial on COM") + char(port+'0');
         }
      }
   }

   CPBFrameWnd *win = new CPBFrameWnd(serial);

   m_pMainWnd = win;

   win->LoadFrame(IDR_SESSIONWINDOW);

   win->ShowWindow(SW_SHOWDEFAULT);
   win->SetWindowText(title);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


// App command to run the dialog
void CPBNodeApp::OnAppAbout()
{
//	CAboutDlg aboutDlg;
//	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPBNodeApp commands
