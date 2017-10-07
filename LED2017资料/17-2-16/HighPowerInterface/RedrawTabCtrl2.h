#if !defined(AFX_REDRAWTABCTRL2_H__A16AC796_5A8C_402B_92E4_0068EEE17E71__INCLUDED_)
#define AFX_REDRAWTABCTRL2_H__A16AC796_5A8C_402B_92E4_0068EEE17E71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RedrawTabCtrl2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRedrawTabCtrl2 window

class CRedrawTabCtrl2 : public CTabCtrl
{
// Construction
public:
	CRedrawTabCtrl2();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRedrawTabCtrl2)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRedrawTabCtrl2();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRedrawTabCtrl2)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDRAWTABCTRL2_H__A16AC796_5A8C_402B_92E4_0068EEE17E71__INCLUDED_)
