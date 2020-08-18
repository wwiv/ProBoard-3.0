// DlgSecLevels.cpp : implementation file
//

#include "stdafx.h"
#include "tslib.hpp"

#include "pb.h"
#include "DlgSecLevels.h"
#include "DlgEditLevel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSecLevels dialog


CDlgSecLevels::CDlgSecLevels(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSecLevels::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSecLevels)
	//}}AFX_DATA_INIT
}


void CDlgSecLevels::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSecLevels)
	DDX_Control(pDX, IDC_LEVELS, m_lbLevels);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSecLevels, CDialog)
	//{{AFX_MSG_MAP(CDlgSecLevels)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_LBN_DBLCLK(IDC_LEVELS, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSecLevels message handlers

BOOL CDlgSecLevels::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   m_lbLevels.AddString("   55\tCoSysOp");
   m_lbLevels.AddString("   30\tNormal");
   m_lbLevels.AddString("  100\tSysOp");

	return TRUE;
}


void CDlgSecLevels::OnDelete() 
{
   m_lbLevels.DeleteString(m_lbLevels.GetCurSel());
}

void CDlgSecLevels::OnEdit() 
{
   int i = m_lbLevels.GetCurSel();

   if(i != LB_ERR)
   {
      int l = m_lbLevels.GetTextLen(i);

      if(l != LB_ERR)
      {
         char *omschr = new char[81];
         char *s = new char[l+1];

         m_lbLevels.GetText(i,s);

         char *p = strtok(s,"\t");

         int level = atoi(p);
         
         p = strtok(NULL,"\t");

         strcpy(omschr,p);

         CdlgEditLevel dlg(this,level,omschr);

         if(dlg.DoModal() == IDOK)
         {
            m_lbLevels.DeleteString(i);
            m_lbLevels.SetSel(m_lbLevels.AddString(form("%5d\t%s",level,omschr)));
         }
      }
   }
}

void CDlgSecLevels::OnNew() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgSecLevels::OnDblclk() 
{
   OnEdit();
}
