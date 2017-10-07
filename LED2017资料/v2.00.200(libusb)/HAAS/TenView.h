// TenView.h : interface of the CTenView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TENVIEW_H__39CA4E2F_ABCB_11D8_A0D0_00055D02EEF1__INCLUDED_)
#define AFX_TENVIEW_H__39CA4E2F_ABCB_11D8_A0D0_00055D02EEF1__INCLUDED_

#include "MySpecDoc.h"
#include "RowView.h"

#define   ROWV_W_SN           6
#define   ROWV_W_SPECT        35
#define   ROWV_W_DATA         80

#define   ROWV_H              9

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTenView : public CRowView
{
protected: // create from serialization only
	DECLARE_DYNCREATE(CTenView)

// Attributes
public:
	CTenView();

// Operations
public:
	CMySpecDoc* GetDocument()
		{
			ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySpecDoc)));
			return (CMySpecDoc*) m_pDocument;
		}
// Overrides of CView
	void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);

// Overrides of CRowView
	void GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight);
	int GetActiveRow();
	int GetRowCount();
	void OnDrawRow(CDC* pDC, int nRowNo, int y, BOOL bSelected);
	void ChangeSelectionNextRow(BOOL bNext);
	void ChangeSelectionToRow(int nRow);

// Implementation
protected:
	virtual ~CTenView();

// Generated message map functions
protected:
	//{{AFX_MSG(CTenView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TENVIEW_H__39CA4E2F_ABCB_11D8_A0D0_00055D02EEF1__INCLUDED_)
