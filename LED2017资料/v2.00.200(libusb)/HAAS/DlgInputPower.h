#if !defined(AFX_DLGINPUTPOWER_H__180A1221_7AFD_11DC_A22A_00E04C7717C9__INCLUDED_)
#define AFX_DLGINPUTPOWER_H__180A1221_7AFD_11DC_A22A_00E04C7717C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInputPower.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInputPower dialog

class CDlgInputPower : public CDialog
{
// Construction
public:
	CDlgInputPower(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInputPower)
	enum { IDD = IDD_INPUT_POWER };
	float	m_fI;
	float	m_fP;
	float	m_fPF;
	float	m_fU;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInputPower)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInputPower)
	afx_msg void OnChangeEditU();
	afx_msg void OnChangeEditI();
	afx_msg void OnChangeEditPf();
	virtual void OnOK();
	afx_msg void OnButton1();
	virtual void OnCancel();
	afx_msg void OnKillfocusEditPf();
	afx_msg void OnKillfocusEditP();
	afx_msg void OnKillfocusEditU();
	afx_msg void OnKillfocusEditI();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINPUTPOWER_H__180A1221_7AFD_11DC_A22A_00E04C7717C9__INCLUDED_)
