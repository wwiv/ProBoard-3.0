// FlagEditPpg.cpp : Implementation of the CFlagEditPropPage property page class.

#include "stdafx.h"
#include "FlagEdit.h"
#include "FlagEditPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CFlagEditPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CFlagEditPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CFlagEditPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CFlagEditPropPage, "FLAGEDIT.FlagEditPropPage.1",
	0xa867ab44, 0x6e55, 0x11d0, 0xac, 0xf, 0, 0xa0, 0x24, 0xd4, 0xe, 0xea)


/////////////////////////////////////////////////////////////////////////////
// CFlagEditPropPage::CFlagEditPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CFlagEditPropPage

BOOL CFlagEditPropPage::CFlagEditPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_FLAGEDIT_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CFlagEditPropPage::CFlagEditPropPage - Constructor

CFlagEditPropPage::CFlagEditPropPage() :
	COlePropertyPage(IDD, IDS_FLAGEDIT_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CFlagEditPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CFlagEditPropPage::DoDataExchange - Moves data between page and properties

void CFlagEditPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CFlagEditPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CFlagEditPropPage message handlers
