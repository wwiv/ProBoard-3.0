// PropOptionsDirectories.cpp : implementation file
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
// CPropOptionsDirectories property page

IMPLEMENT_DYNCREATE(CPropOptionsDirectories, CPropertyPage)

CPropOptionsDirectories::CPropOptionsDirectories() : CPropertyPage(CPropOptionsDirectories::IDD)
{
   //{{AFX_DATA_INIT(CPropOptionsDirectories)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPropOptionsDirectories::~CPropOptionsDirectories()
{
}

void CPropOptionsDirectories::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CPropOptionsDirectories)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropOptionsDirectories, CPropertyPage)
   //{{AFX_MSG_MAP(CPropOptionsDirectories)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropOptionsDirectories message handlers
