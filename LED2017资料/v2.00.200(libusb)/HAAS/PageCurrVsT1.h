#if !defined(AFX_PAGECURRVST1_H__ADC78FB8_A685_47C0_A9AC_C4E06EE64ADC__INCLUDED_)
#define AFX_PAGECURRVST1_H__ADC78FB8_A685_47C0_A9AC_C4E06EE64ADC__INCLUDED_

#include "DrawForMySpec.h"
#define WM_LIST_SELE_T      WM_USER+0x8767

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageCurrVsT1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageCurrVsT1 dialog

class CPageCurrVsT1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageCurrVsT1)

// Construction
public:
	CPageCurrVsT1();
	~CPageCurrVsT1();

// Dialog Data
	//{{AFX_DATA(CPageCurrVsT1)
	enum { IDD = IDD_PAGE_CURR_VS_T1 };
	CListBox	m_cList;
	CDrawForMySpec	m_cDraw;
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageCurrVsT1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageCurrVsT1)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeList();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bFir;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECURRVST1_H__ADC78FB8_A685_47C0_A9AC_C4E06EE64ADC__INCLUDED_)
