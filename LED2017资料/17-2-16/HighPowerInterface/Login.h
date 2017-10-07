#if !defined(AFX_LOGIN_H__BD7A5453_5D62_476E_8DF0_45968DA953F7__INCLUDED_)
#define AFX_LOGIN_H__BD7A5453_5D62_476E_8DF0_45968DA953F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Login.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
#include "ChangePassword.h"
#include "AuthorityView.h"
/////////////////////////////////////////////////////////////////////////////
// CLogin dialog

class CLogin : public CResizingDialog
{
// Construction
public:
	CLogin(CWnd* pParent = NULL);   // standard constructor
	bool login;
	CChangePassword m_changepassword;
	CAuthorityView m_authorityview;
// Dialog Data
	//{{AFX_DATA(CLogin)
	enum { IDD = IDD_Login };
	CButton	m_enterEngineer;
	CBitButtonNL	m_login;
	CBitButtonNL	m_exit;
	CBitButtonNL	m_changePsd;
	//}}AFX_DATA

	void SetDialogFace();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLogin)
	afx_msg void OnExit();
	afx_msg void Onchangepassword();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg bool OnLogin();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnenterEngineer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGIN_H__BD7A5453_5D62_476E_8DF0_45968DA953F7__INCLUDED_)
