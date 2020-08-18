// PropUserEd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropUserSecurity dialog

class CPropUserSecurity : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropUserSecurity)

// Construction
public:
	CPropUserSecurity();
	~CPropUserSecurity();

// Dialog Data
	//{{AFX_DATA(CPropUserSecurity)
	enum { IDD = IDD_PROP_USERED_SECURITY };
	CSpinButtonCtrl	m_SpinDate;
	UINT	m_ExpDateDay;
	int		m_ExpDateMonth;
	CString	m_ExpDateYear;
	int		m_ExpLevel;
	int		m_Level;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropUserSecurity)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropUserSecurity)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
