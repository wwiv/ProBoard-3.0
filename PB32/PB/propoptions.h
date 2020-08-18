// PropOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainProp

class CPropSheetOptions : public CPropertySheet
{
	DECLARE_DYNAMIC(CPropSheetOptions)

// Construction
public:
	CPropSheetOptions(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPropSheetOptions(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropSheetOptions)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropSheetOptions();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPropSheetOptions)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CPropOptionsSecurity : public CPropertyPage
{
   DECLARE_DYNCREATE(CPropOptionsSecurity)

// Construction
public:
   CPropOptionsSecurity();
   ~CPropOptionsSecurity();

// Dialog Data
   //{{AFX_DATA(CPropOptionsSecurity)
	enum { IDD = IDD_PROP_OPT_SECURITY };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
   //{{AFX_VIRTUAL(CPropOptionsSecurity)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
   //{{AFX_MSG(CPropOptionsSecurity)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


class CPropOptionsNewUsers : public CPropertyPage
{
   DECLARE_DYNCREATE(CPropOptionsNewUsers)

// Construction
public:
   CPropOptionsNewUsers();
   ~CPropOptionsNewUsers();

// Dialog Data
   //{{AFX_DATA(CPropOptionsNewUsers)
	enum { IDD = IDD_PROP_OPT_NEWUSERS };
	BOOL	m_Ansi;
	BOOL	m_AskAddress;
	BOOL	m_AskBirthDate;
	BOOL	m_AskCountry;
	BOOL	m_AskDataPhone;
	BOOL	m_AskDateFormat;
	BOOL	m_AskFaxPhone;
	BOOL	m_AskSex;
	BOOL	m_AskState;
	BOOL	m_AskVoice;
	int		m_LogLevel;
	BOOL	m_Avatar;
	UINT	m_Level;
	int		m_ExpLevel;
	CString	m_ExpDateYear;
	int		m_ExpDateMonth;
	UINT	m_ExpDateDay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
   //{{AFX_VIRTUAL(CPropOptionsNewUsers)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
   //{{AFX_MSG(CPropOptionsNewUsers)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

class CPropOptionsDirectories : public CPropertyPage
{
   DECLARE_DYNCREATE(CPropOptionsDirectories)

// Construction
public:
   CPropOptionsDirectories();
   ~CPropOptionsDirectories();

// Dialog Data
   //{{AFX_DATA(CPropOptionsDirectories)
	enum { IDD = IDD_PROP_OPT_DIRECTORIES };
	CString	m_Menus;
	CString	m_MsgBase;
	CString	m_Pex;
	CString	m_Txt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
   //{{AFX_VIRTUAL(CPropOptionsDirectories)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
   //{{AFX_MSG(CPropOptionsDirectories)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};




/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CPropSiteInfo dialog

class CPropSiteInfo : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropSiteInfo)

// Construction
public:
	CPropSiteInfo();
	~CPropSiteInfo();

// Dialog Data
	//{{AFX_DATA(CPropSiteInfo)
	enum { IDD = IDD_PROP_OPT_SITEINFO };
	CString	m_BbsName;
	CString	m_Location;
	CString	m_OriginLine;
	CString	m_SysopName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropSiteInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropSiteInfo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
