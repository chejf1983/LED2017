#if !defined(AFX_CHANGEPASSWORD_H__80C87E00_C0C2_4C44_BFB2_C4FB7BA0BC70__INCLUDED_)
#define AFX_CHANGEPASSWORD_H__80C87E00_C0C2_4C44_BFB2_C4FB7BA0BC70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangePassword.h : header file
//

#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
/////////////////////////////////////////////////////////////////////////////
// CChangePassword dialog

class CChangePassword : public CResizingDialog
{
// Construction
public:
	CChangePassword(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChangePassword)
	enum { IDD = IDD_ChangePassword };
	CBitButtonNL	m_changeexit;
	CBitButtonNL	m_changesure;
	//}}AFX_DATA

	void SetDialogFace();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangePassword)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangePassword)
	afx_msg void OnExit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg bool OnSure();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEPASSWORD_H__80C87E00_C0C2_4C44_BFB2_C4FB7BA0BC70__INCLUDED_)
