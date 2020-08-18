// editmsgarea.cpp : implementation file
//

#include "stdafx.h"
#include "pb.h"
#include "editmsgarea.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEditMsgArea dialog


CDlgEditMsgArea::CDlgEditMsgArea(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditMsgArea::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEditMsgArea)
	m_Name = _T("");
	m_Catalog = _T("");
	m_Location = _T("");
	//}}AFX_DATA_INIT
}


void CDlgEditMsgArea::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEditMsgArea)
	DDX_Text(pDX, IDC_ED_AREANAME, m_Name);
	DDX_Text(pDX, IDC_ED_CATALOGFILE, m_Catalog);
	DDX_Text(pDX, IDC_ED_FILELOCATION, m_Location);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEditMsgArea, CDialog)
	//{{AFX_MSG_MAP(CDlgEditMsgArea)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEditMsgArea message handlers
