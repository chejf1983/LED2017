#if !defined(AFX_DEBUG5_H__42C07DB7_D06B_4510_A6C3_32AD8371AE84__INCLUDED_)
#define AFX_DEBUG5_H__42C07DB7_D06B_4510_A6C3_32AD8371AE84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Debug5.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDebug5 dialog

class CDebug5 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDebug5)

// Construction
public:
	CDebug5();
	~CDebug5();

// Dialog Data
	//{{AFX_DATA(CDebug5)
	enum { IDD = IDD_DEBUG5 };
	CEdit	m_cK3;
	CEdit	m_cK2;
	CEdit	m_cK1;
	CEdit	m_cAD;
	int		m_iRange;
	float	m_fZero1;
	float	m_fZero2;
	float	m_fZero3;
	float	m_fZero4;
	float	m_fZero;
	BOOL	m_bConSample;
	float	m_fI1;
	float	m_fI2;
	float	m_fI3;
	float	m_fI4;
	float	m_fAD1;
	float	m_fAD2;
	float	m_fAD3;
	float	m_fAD4;
	CString	m_strNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDebug5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDebug5)
	afx_msg void OnButtonSave();
	afx_msg void OnButtonZero();
	afx_msg void OnButtonSamp();
	afx_msg void OnCheckSample();
	afx_msg void OnButtonGet();
	afx_msg void OnButtonSend();
	virtual void OnCancel();
	afx_msg void OnButtonCalc();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEBUG5_H__42C07DB7_D06B_4510_A6C3_32AD8371AE84__INCLUDED_)
