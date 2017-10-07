#if !defined(AFX_ENGINEERLOGIN_H__681471B4_5293_4C51_8F58_C5950EA3555E__INCLUDED_)
#define AFX_ENGINEERLOGIN_H__681471B4_5293_4C51_8F58_C5950EA3555E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EngineerLogin.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
/////////////////////////////////////////////////////////////////////////////
// CEngineerLogin dialog

class CEngineerLogin : public CResizingDialog
{
// Construction
public:
	CEngineerLogin(CWnd* pParent = NULL);   // standard constructor
	bool login;
// Dialog Data
	//{{AFX_DATA(CEngineerLogin)
	enum { IDD = IDD_EngineerLogin };
	CBitButtonNL	m_exit;
	CBitButtonNL	m_login;
	//}}AFX_DATA

	void SetDialogFace();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEngineerLogin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEngineerLogin)
	afx_msg void OnLogin();
	afx_msg void OnExit();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENGINEERLOGIN_H__681471B4_5293_4C51_8F58_C5950EA3555E__INCLUDED_)
