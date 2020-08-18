// dlgEditLevel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CdlgEditLevel dialog

class CdlgEditLevel : public CDialog
{
// Construction
   int& level;
   char *omschr;
public:
	CdlgEditLevel(CWnd* pParent,int &, char *);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CdlgEditLevel)
	enum { IDD = IDD_EDIT_SECLEVEL };
	CString	m_descr;
	UINT	m_level;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CdlgEditLevel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CdlgEditLevel)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
