#if !defined(AFX_DEBUG6_H__2E8D2D31_B50C_447C_BB5F_0C1CE3FA5A34__INCLUDED_)
#define AFX_DEBUG6_H__2E8D2D31_B50C_447C_BB5F_0C1CE3FA5A34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Debug6.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDebug6 dialog

class CDebug6 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDebug6)

// Construction
public:
	BOOL bGo;
	CDebug6();
	~CDebug6();

// Dialog Data
	//{{AFX_DATA(CDebug6)
	enum { IDD = IDD_DEBUG6 };
	CButton	m_cCheck;
	CEdit	m_cAD;
	CButton	m_cSave;
	CButton	m_cCal34;
	CButton	m_cCal23;
	CButton	m_cCal12;
	float	m_fZero1;
	float	m_fZero2;
	float	m_fZero3;
	float	m_fZero4;
	int		m_iRange;
	CString	m_strNumber;
	float	m_fAD11;
	float	m_fAD12;
	float	m_fAD21;
	float	m_fAD22;
	float	m_fAD31;
	float	m_fAD32;
	float	m_fK1;
	float	m_fK2;
	float	m_fK3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDebug6)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDebug6)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSaveExit();
	virtual void OnCancel();
	afx_msg void OnButtonSamp();
	afx_msg void OnGetZero();
	afx_msg void OnCal12();
	afx_msg void OnCal23();
	afx_msg void OnCal34();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEBUG6_H__2E8D2D31_B50C_447C_BB5F_0C1CE3FA5A34__INCLUDED_)
