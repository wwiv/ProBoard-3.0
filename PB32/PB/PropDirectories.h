// PropDirectories.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropDirectories dialog

class CPropDirectories : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropDirectories)

// Construction
public:
	CPropDirectories();
	~CPropDirectories();

// Dialog Data
	//{{AFX_DATA(CPropDirectories)
	enum { IDD = IDD_PROP_OPT_DIRECTORIES };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropDirectories)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropDirectories)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
