#if !defined(AFX_PAGECURRVSL1_H__62D558F5_1549_4DF5_8410_F9DB05A4DB10__INCLUDED_)
#define AFX_PAGECURRVSL1_H__62D558F5_1549_4DF5_8410_F9DB05A4DB10__INCLUDED_

#include "DrawForMySpec.h"
#define WM_LIST_SELE         WM_USER+0x8765

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageCurrVsL1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageCurrVsL1 dialog

class CPageCurrVsL1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageCurrVsL1)

// Construction
public:
	CPageCurrVsL1();
	~CPageCurrVsL1();

// Dialog Data
	//{{AFX_DATA(CPageCurrVsL1)
	enum { IDD = IDD_PAGE_CURR_VS_L_1 };
	CListBox	m_cList;
	CDrawForMySpec	m_cDraw;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageCurrVsL1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageCurrVsL1)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bFir;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECURRVSL1_H__62D558F5_1549_4DF5_8410_F9DB05A4DB10__INCLUDED_)
