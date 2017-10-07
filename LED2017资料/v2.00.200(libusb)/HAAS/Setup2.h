#if !defined(AFX_SETUP2_H__AE4055A1_9CBF_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_SETUP2_H__AE4055A1_9CBF_11DB_949D_00055D02EEF1__INCLUDED_

#include "label.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Setup2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetup2 dialog

class CSetup2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetup2)

// Construction
public:
	CSetup2();
	~CSetup2();

// Dialog Data
	//{{AFX_DATA(CSetup2)
	enum { IDD = IDD_SETUP2 };
	CStatic	m_cMode;
	CLabel	m_cWL12;
	CStatic	m_cS2;
	CStatic	m_cS1;
	CComboBox	m_cSTCType;
	CComboBox	m_cSTCCom;
	BOOL	m_bDemo;
	CString	m_strSTCCom;
	CString	m_strSTCType;
	int		m_iDateType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetup2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetup2)
	afx_msg void OnSelchangeComboStcType();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUP2_H__AE4055A1_9CBF_11DB_949D_00055D02EEF1__INCLUDED_)
