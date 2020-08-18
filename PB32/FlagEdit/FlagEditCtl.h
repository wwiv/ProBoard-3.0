// FlagEditCtl.h : Declaration of the CFlagEditCtrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CFlagEditCtrl : See FlagEditCtl.cpp for implementation.

class CFlagEditCtrl : public COleControl
{
	DECLARE_DYNCREATE(CFlagEditCtrl)

// Constructor
public:
	CFlagEditCtrl();

// Overrides

	// Drawing function
	virtual void OnDraw(
				CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);

	// Persistence
	virtual void DoPropExchange(CPropExchange* pPX);

	// Reset control state
	virtual void OnResetState();

// Implementation
protected:
	~CFlagEditCtrl();

	DECLARE_OLECREATE_EX(CFlagEditCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CFlagEditCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CFlagEditCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CFlagEditCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CFlagEditCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CFlagEditCtrl)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CFlagEditCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CFlagEditCtrl)
	//}}AFX_DISP_ID
	};
};
