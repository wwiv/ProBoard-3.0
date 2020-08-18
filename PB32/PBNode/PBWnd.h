#ifndef __PBWND_H
#define __PBWND_H

#include "ttywnd.h"
#include "pbthread.h"
#include "serial.h"


// PBWnd.h : header file
//

class GFComLink;

/////////////////////////////////////////////////////////////////////////////
// CPBWnd window

class CPBWnd : public CTTYWnd
{
   CPBThread *mainThread;

   CSerial *serial;

// Construction
public:
	CPBWnd(CSerial *);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPBWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPBWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPBWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif
