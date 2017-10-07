#if !defined(AFX_OPTION1_H__71AD1D01_0B63_11DB_949C_00055D02EEF1__INCLUDED_)
#define AFX_OPTION1_H__71AD1D01_0B63_11DB_949C_00055D02EEF1__INCLUDED_

#include "Label.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Option1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COption1 dialog

class COption1 : public CPropertyPage
{
	DECLARE_DYNCREATE(COption1)

// Construction
public:
	void MSPAINT(CString strPathName);
	COption1();
	~COption1();

// Dialog Data
	//{{AFX_DATA(COption1)
	enum { IDD = IDD_OPTION1 };
	CComboBox	m_cPrintLogoPos;
	CLabel	m_cLogo;
	CString	m_strIntervalWL;
	BOOL	m_bPrintLogo;
	int		m_iPrintLogoPos;
	int		m_iReportType;
	BOOL	m_bPrintPage;
	int		m_iShowCIE;
	CString	m_strPrTitle;
	int		m_iPrintG;
	CString	m_strAddr;
	CString	m_strCompany;
	int		m_iNType;
	CString	m_strChecker;
	BOOL	m_bPrintChecker;
	CString	m_strNewT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COption1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COption1)
	afx_msg void OnCheckPrintLogo();
	virtual BOOL OnInitDialog();
	afx_msg void OnStaticLogo();
	afx_msg void OnEditchangeComboIntervalWl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTION1_H__71AD1D01_0B63_11DB_949C_00055D02EEF1__INCLUDED_)
