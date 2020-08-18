// PropNewUsers.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropNewUsers dialog

class CPropNewUsers : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropNewUsers)

// Construction
public:
	CPropNewUsers();
	~CPropNewUsers();

// Dialog Data
	//{{AFX_DATA(CPropNewUsers)
	enum { IDD = IDD_PROP_OPT_NEWUSERS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropNewUsers)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropNewUsers)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
