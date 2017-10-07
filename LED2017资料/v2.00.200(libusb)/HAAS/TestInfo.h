#if !defined(AFX_TESTINFO_H__2AFC0F81_E2F4_11D9_ABAD_00055D02EEF1__INCLUDED_)
#define AFX_TESTINFO_H__2AFC0F81_E2F4_11D9_ABAD_00055D02EEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestInfo dialog

class CTestInfo : public CDialog
{
// Construction
public:
	CTestInfo(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CTestInfo)
	enum { IDD = IDD_TEST_INFO };
	CString	m_strDate;
	CString	m_strFactory;
	CString	m_strH;
	CString	m_strModel;
	CString	m_strNumber;
	CString	m_strRemark;
	CString	m_strT;
	CString	m_strTester;
	CString	m_strName;
	CString	m_strStandard;
	CString	m_strState;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestInfo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTINFO_H__2AFC0F81_E2F4_11D9_ABAD_00055D02EEF1__INCLUDED_)
