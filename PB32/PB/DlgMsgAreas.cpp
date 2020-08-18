// DlgMsgAreas.cpp : implementation file
//

#include "stdafx.h"
#include "pb.h"
#include "pblib.hpp"

#include "DlgMsgAreas.h"
#include "editmsgarea.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMsgAreas dialog


CDlgMsgAreas::CDlgMsgAreas(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMsgAreas::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMsgAreas)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgMsgAreas::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMsgAreas)
	DDX_Control(pDX, IDC_LISTBOX, m_ListBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMsgAreas, CDialog)
	//{{AFX_MSG_MAP(CDlgMsgAreas)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMsgAreas message handlers

BOOL CDlgMsgAreas::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   QFile f;
   
   f.open("FILEAREA.PB",fmode_rw);

   _TpFileArea ma;

   for(int i=1;;i++)
   {
      if(f.read(&ma,sizeof(ma)) != sizeof(ma))
         break;

      m_ListBox.AddString(form("%d\t%s",i,ma.name));
   }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMsgAreas::OnEdit() 
{
   int n = m_ListBox.GetCurSel();

   if(n >= 0)
   {
      _TpFileArea fa;
      QFile f;
      
      f.open("FILEAREA.PB",fmode_rw);

      f.seek(n * sizeof(_TpFileArea));
      f.read(&fa,sizeof(fa));

      CDlgEditMsgArea dlg;

      dlg.m_Name = fa.name;
      dlg.m_Catalog = fa.listPath;
      dlg.m_Location = fa.filePath;

      dlg.DoModal();
   }
}
