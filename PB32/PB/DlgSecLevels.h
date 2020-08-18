// DlgSecLevels.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSecLevels dialog

#include "listboxseclev.h"

class CDlgSecLevels : public CDialog
{
// Construction
public:
	CDlgSecLevels(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSecLevels)
	enum { IDD = IDD_SECLEVELS };
	CListBoxSecLev	m_lbLevels;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSecLevels)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSecLevels)
	virtual BOOL OnInitDialog();
	afx_msg void OnDelete();
	afx_msg void OnEdit();
	afx_msg void OnNew();
	afx_msg void OnDblclk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
