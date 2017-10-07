#if !defined(AFX_REGISTERDLG_H__05B2FEC7_0BB7_465E_833A_B52F56171057__INCLUDED_)
#define AFX_REGISTERDLG_H__05B2FEC7_0BB7_465E_833A_B52F56171057__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegisterDlg.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg dialog

class CRegisterDlg : public CResizingDialog
{
// Construction
public:
	CRegisterDlg(CWnd* pParent = NULL);   // standard constructor
	int registTime;

// Dialog Data
	//{{AFX_DATA(CRegisterDlg)
	enum { IDD = IDD_Register };
	CBitButtonNL	m_register;
	CBitButtonNL	m_cancel;
	CString	m_code1;
	CString	m_code2;
	CString	m_code3;
	CString	m_code4;
	//}}AFX_DATA

	void SetDialogFace();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegisterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegisterDlg)
	afx_msg void OnRegister();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnChangeRegCode1();
	afx_msg void OnChangeRegCode2();
	afx_msg void OnChangeRegCode3();
	afx_msg void OnChangeRegCode4();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTERDLG_H__05B2FEC7_0BB7_465E_833A_B52F56171057__INCLUDED_)
