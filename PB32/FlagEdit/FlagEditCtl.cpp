// FlagEditCtl.cpp : Implementation of the CFlagEditCtrl OLE control class.

#include "stdafx.h"
#include "FlagEdit.h"
#include "FlagEditCtl.h"
#include "FlagEditPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CFlagEditCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CFlagEditCtrl, COleControl)
	//{{AFX_MSG_MAP(CFlagEditCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CFlagEditCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CFlagEditCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CFlagEditCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CFlagEditCtrl, COleControl)
	//{{AFX_EVENT_MAP(CFlagEditCtrl)
	EVENT_STOCK_CLICK()
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CFlagEditCtrl, 1)
	PROPPAGEID(CFlagEditPropPage::guid)
END_PROPPAGEIDS(CFlagEditCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CFlagEditCtrl, "FLAGEDIT.FlagEditCtrl.1",
	0xa867ab43, 0x6e55, 0x11d0, 0xac, 0xf, 0, 0xa0, 0x24, 0xd4, 0xe, 0xea)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CFlagEditCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DFlagEdit =
		{ 0xa867ab41, 0x6e55, 0x11d0, { 0xac, 0xf, 0, 0xa0, 0x24, 0xd4, 0xe, 0xea } };
const IID BASED_CODE IID_DFlagEditEvents =
		{ 0xa867ab42, 0x6e55, 0x11d0, { 0xac, 0xf, 0, 0xa0, 0x24, 0xd4, 0xe, 0xea } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwFlagEditOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CFlagEditCtrl, IDS_FLAGEDIT, _dwFlagEditOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CFlagEditCtrl::CFlagEditCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CFlagEditCtrl

BOOL CFlagEditCtrl::CFlagEditCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_FLAGEDIT,
			IDB_FLAGEDIT,
			TRUE,                       //  Insertable
			_dwFlagEditOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CFlagEditCtrl::CFlagEditCtrl - Constructor

CFlagEditCtrl::CFlagEditCtrl()
{
	InitializeIIDs(&IID_DFlagEdit, &IID_DFlagEditEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CFlagEditCtrl::~CFlagEditCtrl - Destructor

CFlagEditCtrl::~CFlagEditCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CFlagEditCtrl::OnDraw - Drawing function

void CFlagEditCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);

   for(int i=0; i<32;i++)
   {
      pdc->TextOut(i*10,10,"A");
   }

}


/////////////////////////////////////////////////////////////////////////////
// CFlagEditCtrl::DoPropExchange - Persistence support

void CFlagEditCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CFlagEditCtrl::OnResetState - Reset control to default state

void CFlagEditCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CFlagEditCtrl::AboutBox - Display an "About" box to the user

void CFlagEditCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_FLAGEDIT);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CFlagEditCtrl message handlers
