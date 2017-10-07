#if !defined(AFX_REDRAWEDIT_H__76C07D6E_49A5_4160_B4DD_634D950B00BA__INCLUDED_)
#define AFX_REDRAWEDIT_H__76C07D6E_49A5_4160_B4DD_634D950B00BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReDrawEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReDrawEdit window

class CReDrawEdit : public CEdit
{
// Construction
public:
	CReDrawEdit();

// Attributes
public:
	HBRUSH m_hBrush;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReDrawEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReDrawEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CReDrawEdit)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDRAWEDIT_H__76C07D6E_49A5_4160_B4DD_634D950B00BA__INCLUDED_)
