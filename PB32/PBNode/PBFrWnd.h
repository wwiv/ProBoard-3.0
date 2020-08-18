#include "pbwnd.h"

// PBFrWnd.h : header file
//

class GFComLink;

/////////////////////////////////////////////////////////////////////////////
// CPBFrameWnd frame

class CPBFrameWnd : public CFrameWnd
{
	//DECLARE_DYNCREATE(CPBFrameWnd)

   CDialog *aboutbox;

public:
   CPBWnd wndClient;
public:
	CPBFrameWnd(CSerial *);           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPBFrameWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPBFrameWnd();

	// Generated message map functions
	//{{AFX_MSG(CPBFrameWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnHangup();
	afx_msg void OnMinimize();
	afx_msg void OnInfront();
	afx_msg void OnAbout();
	afx_msg void OnFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
