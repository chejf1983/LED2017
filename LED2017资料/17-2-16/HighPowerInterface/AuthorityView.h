#if !defined(AFX_AUTHORITYVIEW_H__92542866_A7A3_4560_A89A_A8A8661A805B__INCLUDED_)
#define AFX_AUTHORITYVIEW_H__92542866_A7A3_4560_A89A_A8A8661A805B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AuthorityView.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL/BitButtonNL.h"
/////////////////////////////////////////////////////////////////////////////
// CAuthorityView dialog

class CAuthorityView : public CResizingDialog
{
// Construction
public:
	CAuthorityView(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CAuthorityView)
	enum { IDD = IDD_AuthorityView };
	CBitButtonNL	m_chiptype;
	CBitButtonNL	m_temperature;
	CBitButtonNL	m_showAuthority;
	CBitButtonNL	m_authoritychange;
	//}}AFX_DATA
	void OnShowtemperature();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAuthorityView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAuthorityView)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void Onauthoritychange();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTHORITYVIEW_H__92542866_A7A3_4560_A89A_A8A8661A805B__INCLUDED_)
