#if !defined(AFX_DLGNAME_H__A2DA0C82_1BF8_11DB_949C_00055D02EEF1__INCLUDED_)
#define AFX_DLGNAME_H__A2DA0C82_1BF8_11DB_949C_00055D02EEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgName dialog

class CDlgName : public CDialog
{
// Construction
public:
	CDlgName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgName)
	enum { IDD = IDD_NAME };
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgName)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNAME_H__A2DA0C82_1BF8_11DB_949C_00055D02EEF1__INCLUDED_)
