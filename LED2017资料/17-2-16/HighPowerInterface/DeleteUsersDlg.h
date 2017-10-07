#if !defined(AFX_DELETEUSERSDLG_H__B3F9DB8B_1A0F_44B0_8A5A_4A9DAD4D1C19__INCLUDED_)
#define AFX_DELETEUSERSDLG_H__B3F9DB8B_1A0F_44B0_8A5A_4A9DAD4D1C19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeleteUsersDlg.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL/BitButtonNL.h"
/////////////////////////////////////////////////////////////////////////////
// CDeleteUsersDlg dialog

class CDeleteUsersDlg : public CResizingDialog
{
// Construction
public:
	CDeleteUsersDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDeleteUsersDlg)
	enum { IDD = IDD_DeleteUsersDlg };
	CBitButtonNL	m_delete;
	CBitButtonNL	m_cancel;
	//}}AFX_DATA
	void SetDialogFace();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeleteUsersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeleteUsersDlg)
	afx_msg bool OnDelete();
	afx_msg void OnCancel();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELETEUSERSDLG_H__B3F9DB8B_1A0F_44B0_8A5A_4A9DAD4D1C19__INCLUDED_)
