#if !defined(AFX_SHOWTESTPOPUP_H__943DE922_32C7_4E4B_8213_0789B5B79F89__INCLUDED_)
#define AFX_SHOWTESTPOPUP_H__943DE922_32C7_4E4B_8213_0789B5B79F89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowTestPopup.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
/////////////////////////////////////////////////////////////////////////////
// ShowTestPopup dialog

class ShowTestPopup : public CResizingDialog
{
// Construction
public:
	ShowTestPopup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ShowTestPopup)
	enum { IDD = IDD_ShowTestPopup };
	CListCtrl	m_showtestpopup_list;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ShowTestPopup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ShowTestPopup)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMaximize();
	afx_msg void OnPopup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWTESTPOPUP_H__943DE922_32C7_4E4B_8213_0789B5B79F89__INCLUDED_)
