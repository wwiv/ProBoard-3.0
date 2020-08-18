// StatDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPBStatusDlg dialog

#include "ServerSock.h"

class CPBStatusDlg : public CDialog
{
// Construction
   CServerSocket sock;
public:
	CPBStatusDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPBStatusDlg)
	enum { IDD = IDD_PBWIN_DIALOG };
	CListBox	m_sessions;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPBStatusDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPBStatusDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
   afx_msg void OnShutDown();
	afx_msg void OnAbout();
   afx_msg void OnLocalSession();
	afx_msg void OnUsers();
	afx_msg void OnLevels();
	afx_msg void OnOptDirs();
	afx_msg void OnOptNewusers();
	afx_msg void OnOptSecurity();
	afx_msg void OnSiteinfo();
	afx_msg void OnPaging();
	afx_msg void OnMsgareas();
	//}}AFX_MSG
   
   void OnOptions(int page);
	
   DECLARE_MESSAGE_MAP()
};
