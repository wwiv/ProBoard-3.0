// DlgMsgAreas.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMsgAreas dialog

class CDlgMsgAreas : public CDialog
{
// Construction
public:
	CDlgMsgAreas(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMsgAreas)
	enum { IDD = IDD_AREAS };
	CListBox	m_ListBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMsgAreas)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMsgAreas)
	virtual BOOL OnInitDialog();
	afx_msg void OnEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
