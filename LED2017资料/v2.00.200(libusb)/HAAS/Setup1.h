#if !defined(AFX_SETUP1_H__CF11B481_98DD_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_SETUP1_H__CF11B481_98DD_11DB_949D_00055D02EEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Setup1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetup1 dialog

class CSetup1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetup1)

// Construction
public:
	BOOL SetLimit();
	void ShowState();
	CSetup1();
	~CSetup1();

// Dialog Data
	//{{AFX_DATA(CSetup1)
	enum { IDD = IDD_SETUP1 };
	CEdit	m_cPerTime;
	CEdit	m_cSetCurr;
	CEdit	m_cSetVol;
	CComboBox	m_cSouComm;
	CComboBox	m_cSouType;
	CButton	m_cManuP;
	CComboBox	m_cPowType;
	CComboBox	m_cPowCom;
	BOOL	m_bHavePower;
	CString	m_strPowCom;
	CString	m_strPowType;
	BOOL	m_bManuP;
	int		m_iSouType;
	CString	m_strSouComm;
	BOOL	m_bAuto;
	int		m_iPerTime;
	float	m_fSetVol;
	float	m_fSetCurr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetup1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetup1)
	afx_msg void OnCheckHavePower();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonLampOff();
	afx_msg void OnCheckAuto();
	afx_msg void OnSelchangeComboSou();
	afx_msg void OnButtonSet();
	afx_msg void OnButtonOn2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUP1_H__CF11B481_98DD_11DB_949D_00055D02EEF1__INCLUDED_)
