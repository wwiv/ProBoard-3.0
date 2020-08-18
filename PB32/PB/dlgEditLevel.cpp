// dlgEditLevel.cpp : implementation file
//

#include "stdafx.h"
#include "tslib.hpp"
#include "PB.h"
#include "dlgEditLevel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CdlgEditLevel dialog


CdlgEditLevel::CdlgEditLevel(CWnd* pParent , int& lev, char *o /*=NULL*/)
	: CDialog(CdlgEditLevel::IDD, pParent) ,
     level(lev) ,
     omschr(o)

{
	//{{AFX_DATA_INIT(CdlgEditLevel)
	m_descr = _T("");
	m_level = 0;
	//}}AFX_DATA_INIT

   m_descr = omschr;
   m_level = level;
}


void CdlgEditLevel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CdlgEditLevel)
	DDX_Text(pDX, IDC_DESCRIPTION, m_descr);
	DDV_MaxChars(pDX, m_descr, 50);
	DDX_Text(pDX, IDC_LEVEL, m_level);
	DDV_MinMaxUInt(pDX, m_level, 1, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CdlgEditLevel, CDialog)
	//{{AFX_MSG_MAP(CdlgEditLevel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CdlgEditLevel message handlers

void CdlgEditLevel::OnOK() 
{
   level = m_level;
   strcpy(omschr,m_descr);

	CDialog::OnOK();
}

BOOL CdlgEditLevel::OnInitDialog() 
{
   CDialog::OnInitDialog();
   
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
