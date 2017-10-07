#if !defined(AFX_PAGE5_H__1A445E96_D1C7_491C_84E6_8AD7ACAAC5BA__INCLUDED_)
#define AFX_PAGE5_H__1A445E96_D1C7_491C_84E6_8AD7ACAAC5BA__INCLUDED_

#include "Label.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page5.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage5 dialog

class CPage5 : public CDialog
{
// Construction
public:

	BOOL m_bFir;
	CPage5(CWnd* pParent = NULL);   // standard constructor

	DECLARE_DYNCREATE(CPage5)

// Dialog Data
	//{{AFX_DATA(CPage5)
	enum { IDD = IDD_PAGE5 };
	CLabel	m_cColor;
	CLabel	m_cPass;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPage5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPage5)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetPos();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE5_H__1A445E96_D1C7_491C_84E6_8AD7ACAAC5BA__INCLUDED_)
