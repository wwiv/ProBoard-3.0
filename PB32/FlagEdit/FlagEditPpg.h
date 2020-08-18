// FlagEditPpg.h : Declaration of the CFlagEditPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CFlagEditPropPage : See FlagEditPpg.cpp.cpp for implementation.

class CFlagEditPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CFlagEditPropPage)
	DECLARE_OLECREATE_EX(CFlagEditPropPage)

// Constructor
public:
	CFlagEditPropPage();

// Dialog Data
	//{{AFX_DATA(CFlagEditPropPage)
	enum { IDD = IDD_PROPPAGE_FLAGEDIT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CFlagEditPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
