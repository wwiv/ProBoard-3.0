// editmsgarea.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEditMsgArea dialog

class CDlgEditMsgArea : public CDialog
{
// Construction
public:
	CDlgEditMsgArea(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEditMsgArea)
	enum { IDD = IDD_MSGAREA };
	CString	m_Name;
	CString	m_Catalog;
	CString	m_Location;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEditMsgArea)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEditMsgArea)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
