#if !defined(AFX_PAGE2_H__ED9FC463_9CA1_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_PAGE2_H__ED9FC463_9CA1_11DB_949D_00055D02EEF1__INCLUDED_

#include "SpectData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage2 dialog

class CPage2 : public CDialog
{
// Construction
public:

	void UpdateShow();
	CSpectData *m_pSpData;
	BOOL m_bFir;
	void SetPos();
	CPage2(CWnd* pParent = NULL);   // standard constructor

	DECLARE_DYNCREATE(CPage2)

// Dialog Data
	//{{AFX_DATA(CPage2)
	enum { IDD = IDD_PAGE2 };
	CStatic	m_cCIE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPage2)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE2_H__ED9FC463_9CA1_11DB_949D_00055D02EEF1__INCLUDED_)
