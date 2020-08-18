// MainProp.cpp : implementation file
//

#include "stdafx.h"
#include "PB.h"
#include "PropOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropSheetOptions

IMPLEMENT_DYNAMIC(CPropSheetOptions, CPropertySheet)

CPropSheetOptions::CPropSheetOptions(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CPropSheetOptions::CPropSheetOptions(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CPropSheetOptions::~CPropSheetOptions()
{
}


BEGIN_MESSAGE_MAP(CPropSheetOptions, CPropertySheet)
   //{{AFX_MSG_MAP(CPropSheetOptions)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CPropOptionsDirectories, CPropertyPage)

CPropOptionsDirectories::CPropOptionsDirectories() : CPropertyPage(CPropOptionsDirectories::IDD)
{
   //{{AFX_DATA_INIT(CPropOptionsDirectories)
	m_Menus = _T("");
	m_MsgBase = _T("");
	m_Pex = _T("");
	m_Txt = _T("");
	//}}AFX_DATA_INIT
}

CPropOptionsDirectories::~CPropOptionsDirectories()
{
}

void CPropOptionsDirectories::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPropOptionsDirectories)
	DDX_Text(pDX, IDC_ED_MENUS, m_Menus);
	DDX_Text(pDX, IDC_ED_MSGBASE, m_MsgBase);
	DDX_Text(pDX, IDC_ED_PEX, m_Pex);
	DDX_Text(pDX, IDC_ED_TXTFILES, m_Txt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropOptionsDirectories, CPropertyPage)
   //{{AFX_MSG_MAP(CPropOptionsDirectories)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


IMPLEMENT_DYNCREATE(CPropOptionsNewUsers, CPropertyPage)

CPropOptionsNewUsers::CPropOptionsNewUsers() : CPropertyPage(CPropOptionsNewUsers::IDD)
{
	//{{AFX_DATA_INIT(CPropOptionsNewUsers)
	m_Ansi = FALSE;
	m_AskAddress = FALSE;
	m_AskBirthDate = FALSE;
	m_AskCountry = FALSE;
	m_AskDataPhone = FALSE;
	m_AskDateFormat = FALSE;
	m_AskFaxPhone = FALSE;
	m_AskSex = FALSE;
	m_AskState = FALSE;
	m_AskVoice = FALSE;
	m_LogLevel = -1;
	m_Avatar = FALSE;
	m_Level = 0;
	m_ExpLevel = -1;
	m_ExpDateYear = _T("");
	m_ExpDateMonth = -1;
	m_ExpDateDay = 0;
	//}}AFX_DATA_INIT
}

CPropOptionsNewUsers::~CPropOptionsNewUsers()
{
}

void CPropOptionsNewUsers::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropOptionsNewUsers)
	DDX_Check(pDX, IDC_ANSI, m_Ansi);
	DDX_Check(pDX, IDC_ASKADDRESS, m_AskAddress);
	DDX_Check(pDX, IDC_ASKBIRTHDATE, m_AskBirthDate);
	DDX_Check(pDX, IDC_ASKCOUNTRY, m_AskCountry);
	DDX_Check(pDX, IDC_ASKDATAPHONE, m_AskDataPhone);
	DDX_Check(pDX, IDC_ASKDATEFMT, m_AskDateFormat);
	DDX_Check(pDX, IDC_ASKFAXPHONE, m_AskFaxPhone);
	DDX_Check(pDX, IDC_ASKSEX, m_AskSex);
	DDX_Check(pDX, IDC_ASKSTATE, m_AskState);
	DDX_Check(pDX, IDC_ASKVOICE, m_AskVoice);
	DDX_CBIndex(pDX, IDC_LOGLEVEL, m_LogLevel);
	DDX_Check(pDX, IDC_AVATAR, m_Avatar);
	DDX_Text(pDX, IDC_LEVEL, m_Level);
	DDV_MinMaxUInt(pDX, m_Level, 0, 65000);
	DDX_CBIndex(pDX, IDC_EXPLEVEL, m_ExpLevel);
	DDX_CBString(pDX, IDC_EXPDATE_YEAR, m_ExpDateYear);
	DDX_CBIndex(pDX, IDC_EXPDATE_MONTH, m_ExpDateMonth);
	DDX_Text(pDX, IDC_EXPDATE_DAY, m_ExpDateDay);
	DDV_MinMaxUInt(pDX, m_ExpDateDay, 0, 31);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropOptionsNewUsers, CPropertyPage)
	//{{AFX_MSG_MAP(CPropOptionsNewUsers)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CPropOptionsSecurity, CPropertyPage)

CPropOptionsSecurity::CPropOptionsSecurity() : CPropertyPage(CPropOptionsSecurity::IDD)
{
	//{{AFX_DATA_INIT(CPropOptionsSecurity)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPropOptionsSecurity::~CPropOptionsSecurity()
{
}

void CPropOptionsSecurity::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropOptionsSecurity)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropOptionsSecurity, CPropertyPage)
	//{{AFX_MSG_MAP(CPropOptionsSecurity)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CPropSheetOptions message handlers
/////////////////////////////////////////////////////////////////////////////
// CPropSiteInfo property page

IMPLEMENT_DYNCREATE(CPropSiteInfo, CPropertyPage)

CPropSiteInfo::CPropSiteInfo() : CPropertyPage(CPropSiteInfo::IDD)
{
	//{{AFX_DATA_INIT(CPropSiteInfo)
	m_BbsName = _T("");
	m_Location = _T("");
	m_OriginLine = _T("");
	m_SysopName = _T("");
	//}}AFX_DATA_INIT
}

CPropSiteInfo::~CPropSiteInfo()
{
}

void CPropSiteInfo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropSiteInfo)
	DDX_Text(pDX, IDC_EDIT_BBSNAME, m_BbsName);
	DDX_Text(pDX, IDC_EDIT_LOCATION, m_Location);
	DDX_Text(pDX, IDC_EDIT_ORIGINLINE, m_OriginLine);
	DDX_Text(pDX, IDC_EDIT_SYSOPNAME, m_SysopName);
	DDV_MaxChars(pDX, m_SysopName, 35);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropSiteInfo, CPropertyPage)
	//{{AFX_MSG_MAP(CPropSiteInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropSiteInfo message handlers
