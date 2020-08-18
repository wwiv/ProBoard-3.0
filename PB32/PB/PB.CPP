// PB.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "pblib.hpp"

#include "PB.h"
#include "StatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPBApp

BEGIN_MESSAGE_MAP(CPBApp, CWinApp)
	//{{AFX_MSG_MAP(CPBApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPBApp construction

CPBApp::CPBApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPBApp object

CPBApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPBApp initialization

_TpConfig cfg;

BOOL CPBApp::InitInstance()
{
	// CG: This line was added by the OLE Control Containment component
	AfxEnableControlContainer();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	QFile f;
   
	f.open("CONFIG.PB");

	f.read(&cfg,sizeof(cfg));
	f.close();

	CPBStatusDlg dlg;
	m_pMainWnd = &dlg;
   
	dlg.DoModal();

	return FALSE;
}
