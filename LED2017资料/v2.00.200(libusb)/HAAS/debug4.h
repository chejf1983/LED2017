#if !defined(AFX_Debug4_H__95920409_F14C_42E2_BFCC_F4A1F9D8568D__INCLUDED_)
#define AFX_Debug4_H__95920409_F14C_42E2_BFCC_F4A1F9D8568D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Debug4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDebug4 dialog

class CDebug4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDebug4)

// Construction
public:
	CDebug4();
	~CDebug4();

// Dialog Data
	//{{AFX_DATA(CDebug4)
	enum { IDD = IDD_DEBUG4 };
	CEdit	m_cTMPCalc;
	CButton	m_cSamp;
	CEdit	m_cR3;
	CEdit	m_cRAD3;
	CButton	m_cTEMP;
	CEdit	m_cTMP;
	CEdit	m_cRAD2;
	CEdit	m_cRAD1;
	CEdit	m_cR2;
	CEdit	m_cR1;
	CEdit	m_cK3;
	CEdit	m_cK2;
	CEdit	m_cK1;
	CEdit	m_cAD;
	int		m_iRange;
	float	m_fZero;
	float	m_fZero1;
	float	m_fZero2;
	float	m_fZero3;
	float	m_fZero4;
	int		m_iTmpType;
	float	m_fR1;
	float	m_fR2;
	float	m_fR3;
	float	m_fADCalc;
	int		m_iRAD1;
	int		m_iRAD2;
	int		m_iRAD3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDebug4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL bGo;
	BOOL bSamp;
	BOOL bTmp;
	// Generated message map functions
	//{{AFX_MSG(CDebug4)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonZero();
	afx_msg void OnButtonSamp();
	afx_msg void OnButtonGet();
	afx_msg void OnButtonSend();
	virtual void OnCancel();
	afx_msg void OnButtonSave();
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	afx_msg void OnButton2();
	afx_msg void OnButton4();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton5();
	afx_msg void OnButtonReset();
	afx_msg void OnRadioColor1();
	afx_msg void OnRadioColor2();
	afx_msg void OnRadioColor3();
	afx_msg void OnRadioColor4();
	afx_msg void OnRadioColor5();
	afx_msg void OnRadioColor6();
	afx_msg void OnRadioColor7();
	afx_msg void OnRadioColor8();
	afx_msg void OnButtonCalc();
	afx_msg void OnButton6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Debug4_H__95920409_F14C_42E2_BFCC_F4A1F9D8568D__INCLUDED_)
