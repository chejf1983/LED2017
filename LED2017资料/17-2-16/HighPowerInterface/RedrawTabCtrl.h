#if !defined(AFX_REDRAWTABCTRL_H__DD80BA18_5EF8_4863_8D7B_70386CF50BDF__INCLUDED_)
#define AFX_REDRAWTABCTRL_H__DD80BA18_5EF8_4863_8D7B_70386CF50BDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RedrawTabCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRedrawTabCtrl window

enum
{
	BTC_NONE = 0,
	BTC_TABS = 1,
	BTC_ALL = 2,
};

enum
{
	ETC_COLOR = 2,
	ETC_SELECTION = 4,
	ETC_GRADIENT = 8,
};

class CRedrawTabCtrl : public CTabCtrl
{
// Construction
public:
	CRedrawTabCtrl();
	void SetBKgndColor(COLORREF color);
	bool EnableDraw(int nType);
	void EnableCustomLook(DWORD dwStyle);
	void Init();
// Attributes
public:
	COLORREF m_bkcolor;
	int m_nDrawType;
	static DWORD s_dwCustomLook;
	RECT rect; 
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRedrawTabCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRedrawTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRedrawTabCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDRAWTABCTRL_H__DD80BA18_5EF8_4863_8D7B_70386CF50BDF__INCLUDED_)
