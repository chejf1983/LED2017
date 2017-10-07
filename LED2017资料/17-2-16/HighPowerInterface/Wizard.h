#if !defined(AFX_WIZARD_H__4AD5284D_F319_42F7_9842_963F7E293CD5__INCLUDED_)
#define AFX_WIZARD_H__4AD5284D_F319_42F7_9842_963F7E293CD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Wizard.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CWizard


class CWizard : public CPropertySheet
{
	DECLARE_DYNAMIC(CWizard)

// Construction
public:
	CWizard(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CWizard(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizard)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizard();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWizard)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARD_H__4AD5284D_F319_42F7_9842_963F7E293CD5__INCLUDED_)
