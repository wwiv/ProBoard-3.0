// ListBoxSecLev.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListBoxSecLev window

class CListBoxSecLev : public CListBox
{
// Construction
public:
	CListBoxSecLev();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxSecLev)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListBoxSecLev();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListBoxSecLev)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
