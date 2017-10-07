#if !defined(AFX_DEBUG3_H__6C77C861_97F6_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_DEBUG3_H__6C77C861_97F6_11DB_949D_00055D02EEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Debug3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDebug3 dialog

class CDebug3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDebug3)

// Construction
public:
	CDebug3();
	~CDebug3();

// Dialog Data
	//{{AFX_DATA(CDebug3)
	enum { IDD = IDD_DEBUG3 };
	CComboBox	m_cReadSN;
	CEdit	m_cWriteSN;
	double	m_fC2;
	double	m_fC3;
	double	m_fC4;
	double	m_fC1;
	int		m_iBaud;
	CString	m_strDriver;
	CString	m_strEprom;
	CString	m_strSoftVer;
	CString	m_strSN;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDebug3)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDebug3)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSOn();
	afx_msg void OnButtonSOff();
	afx_msg void OnButtonWSn();
	afx_msg void OnButtonRSn();
	afx_msg void OnButtonWCor();
	afx_msg void OnButtonRCor();
	afx_msg void OnButtonModSn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEBUG3_H__6C77C861_97F6_11DB_949D_00055D02EEF1__INCLUDED_)
