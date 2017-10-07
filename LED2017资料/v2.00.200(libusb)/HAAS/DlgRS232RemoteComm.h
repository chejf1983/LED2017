#if !defined(AFX_DLGRS232REMOTECOMM_H__995013BB_2E13_47EF_B2B5_C2394B781A06__INCLUDED_)
#define AFX_DLGRS232REMOTECOMM_H__995013BB_2E13_47EF_B2B5_C2394B781A06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRS232RemoteComm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRS232RemoteComm dialog

class CDlgRS232RemoteComm : public CDialog
{
// Construction
public:
	CDlgRS232RemoteComm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRS232RemoteComm)
	enum { IDD = IDD_RS232_REMOTE_COMM };
	CButton	m_cExit;
	CButton	m_cStop;
	CButton	m_cStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRS232RemoteComm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRS232RemoteComm)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRS232REMOTECOMM_H__995013BB_2E13_47EF_B2B5_C2394B781A06__INCLUDED_)
