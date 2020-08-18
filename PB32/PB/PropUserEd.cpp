// PropUserEd.cpp : implementation file
//

#include "stdafx.h"
#include "pb.h"
#include "PropUserEd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropUserSecurity property page

IMPLEMENT_DYNCREATE(CPropUserSecurity, CPropertyPage)

CPropUserSecurity::CPropUserSecurity() : CPropertyPage(CPropUserSecurity::IDD)
{
	//{{AFX_DATA_INIT(CPropUserSecurity)
	m_ExpDateDay = 1;
	m_ExpDateMonth = -1;
	m_ExpDateYear = _T("");
	m_ExpLevel = -1;
	m_Level = -1;
	//}}AFX_DATA_INIT
}

CPropUserSecurity::~CPropUserSecurity()
{
}

void CPropUserSecurity::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropUserSecurity)
	DDX_Control(pDX, IDC_SPIN1, m_SpinDate);
	DDX_Text(pDX, IDC_EXPDATE_DAY, m_ExpDateDay);
	DDV_MinMaxUInt(pDX, m_ExpDateDay, 1, 31);
	DDX_CBIndex(pDX, IDC_EXPDATE_MONTH, m_ExpDateMonth);
	DDX_CBString(pDX, IDC_EXPDATE_YEAR, m_ExpDateYear);
	DDX_CBIndex(pDX, IDC_EXPLEVEL, m_ExpLevel);
	DDX_CBIndex(pDX, IDC_LEVEL, m_Level);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropUserSecurity, CPropertyPage)
	//{{AFX_MSG_MAP(CPropUserSecurity)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropUserSecurity message handlers

BOOL CPropUserSecurity::OnInitDialog() 
{
   CPropertyPage::OnInitDialog();
	
   m_SpinDate.SetRange(1,31);
   
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
