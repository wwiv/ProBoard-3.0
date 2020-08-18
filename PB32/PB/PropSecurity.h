// PropSecurity.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropSecurity dialog

class CPropSecurity : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropSecurity)

// Construction
public:
	CPropSecurity();
	~CPropSecurity();

// Dialog Data
	//{{AFX_DATA(CPropSecurity)
	enum { IDD = IDD_PROP_OPT_SECURITY };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropSecurity)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropSecurity)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
