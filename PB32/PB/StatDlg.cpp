// StatDlg.cpp : implementation file
//

#include "stdafx.h"

#include "pblib.hpp"

#include "PB.h"
#include "StatDlg.h"

#include "dlgseclevels.h"
#include "PropOptions.h"
#include "PropUserEd.h"
#include "DlgMsgAreas.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern _TpConfig cfg;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPBStatusDlg dialog

CPBStatusDlg::CPBStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPBStatusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPBStatusDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPBStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPBStatusDlg)
	DDX_Control(pDX, IDC_LB_SESSIONS, m_sessions);
	//}}AFX_DATA_MAP
//
}

BEGIN_MESSAGE_MAP(CPBStatusDlg, CDialog)
	//{{AFX_MSG_MAP(CPBStatusDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_COMMAND(IDC_SHUTDOWN,OnShutDown)
	ON_COMMAND(IDC_ABOUT, OnAbout)
   ON_COMMAND(IDC_LOCAL, OnLocalSession)
	ON_COMMAND(IDM_USERS, OnUsers)
	ON_COMMAND(IDM_LEVELS, OnLevels)
	ON_COMMAND(IDM_OPT_DIRS, OnOptDirs)
	ON_COMMAND(IDM_OPT_NEWUSERS, OnOptNewusers)
	ON_COMMAND(IDM_OPT_SECURITY, OnOptSecurity)
	ON_COMMAND(IDM_SITEINFO, OnSiteinfo)
	ON_COMMAND(IDM_PAGING, OnPaging)
	ON_COMMAND(IDM_MSGAREAS, OnMsgareas)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPBStatusDlg message handlers

BOOL CPBStatusDlg::OnInitDialog()
{
   sock.Create();
   sock.Listen();

	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPBStatusDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPBStatusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPBStatusDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPBStatusDlg::OnShutDown()
{
   PostMessage(WM_QUIT,0);
}

void CPBStatusDlg::OnLocalSession()
{
   static PROCESS_INFORMATION pinfo;
   STARTUPINFO info;

   memset(&info,0,sizeof(info));

   info.cb = sizeof(info);

   CreateProcess("PBNODE.EXE",NULL,NULL,NULL,TRUE,0,NULL,NULL,&info,&pinfo);
}


void
CPBStatusDlg::OnAbout()
{
	CAboutDlg().DoModal();
}


void
CPBStatusDlg::OnUsers()
{
   CPropertySheet prop("Users",this);

   CPropertyPage pag1(IDD_PROP_USERED_GENERAL);
   CPropUserSecurity pag2;

   prop.AddPage(&pag1);
   prop.AddPage(&pag2);

   prop.DoModal();
}

void
CPBStatusDlg::OnLevels()
{
   CDlgSecLevels dlg;

   dlg.DoModal();
}

void CPBStatusDlg::OnOptDirs() 
{
   OnOptions(0);
}

void CPBStatusDlg::OnOptions(int page)
{
   CPropSheetOptions dlg("Options");

   CPropOptionsDirectories pagdir;
   CPropOptionsNewUsers pagnewuser;
   CPropOptionsSecurity pag3;
   CPropSiteInfo pagsiteinfo;

   pagdir.m_Txt = cfg.txtPath;
   pagdir.m_Menus = cfg.mnuPath;
   pagdir.m_Pex = cfg.pexPath;
   pagdir.m_MsgBase = cfg.msgPath;
   
   pagnewuser.m_Ansi          = cfg.allowAnsi;
   pagnewuser.m_Avatar        = cfg.allowAvatar;
   pagnewuser.m_AskAddress    = cfg.askAddress;
   pagnewuser.m_AskVoice      = cfg.askVoicePhone;
	pagnewuser.m_AskBirthDate  = cfg.askBirthDay;
	pagnewuser.m_AskCountry    = cfg.askCountry;
	pagnewuser.m_AskDataPhone  = cfg.askDataPhone;
	pagnewuser.m_AskDateFormat = cfg.askDateFormat;
	pagnewuser.m_AskFaxPhone   = cfg.askFaxPhone;
	pagnewuser.m_AskSex        = cfg.askSex;
	pagnewuser.m_AskState      = cfg.askState;
	pagnewuser.m_AskVoice      = cfg.askVoicePhone;
	
   pagnewuser.m_Level         = cfg.newUserLevel;
	pagnewuser.m_LogLevel      = cfg.newUserLogLevel;
  
   pagsiteinfo.m_BbsName      = cfg.bbsName;
   pagsiteinfo.m_Location     = cfg.location;
   pagsiteinfo.m_SysopName    = cfg.sysopName;
   pagsiteinfo.m_OriginLine   = cfg.originLine;



   dlg.AddPage(&pagdir);
   dlg.AddPage(&pagnewuser);
   dlg.AddPage(&pag3);
   dlg.AddPage(&pagsiteinfo);

   dlg.SetActivePage(page);
   
   
   if(dlg.DoModal() == IDOK)
   {
      strcpy(cfg.txtPath,pagdir.m_Txt);
      strcpy(cfg.mnuPath,pagdir.m_Menus);
      strcpy(cfg.pexPath,pagdir.m_Pex);
      strcpy(cfg.msgPath,pagdir.m_MsgBase);
   }
}

void CPBStatusDlg::OnOptNewusers() 
{
   OnOptions(1);
}

void CPBStatusDlg::OnOptSecurity() 
{
   OnOptions(2);
}

void CPBStatusDlg::OnSiteinfo() 
{
   OnOptions(3);
}

void CPBStatusDlg::OnPaging() 
{
}

void CPBStatusDlg::OnMsgareas() 
{
   CDlgMsgAreas dlg;

   dlg.DoModal();
}
