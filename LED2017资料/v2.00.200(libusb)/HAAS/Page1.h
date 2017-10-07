#if !defined(AFX_PAGE1_H__ED9FC462_9CA1_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_PAGE1_H__ED9FC462_9CA1_11DB_949D_00055D02EEF1__INCLUDED_

#include "DrawForMySpec.h"
#include "SpectData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage1 dialog

class CPage1 : public CDialog
{
// Construction
public:
	void ReDraw(int iSele=0,int iSDCM1=5,int iSDCM2=6);
	void SetPos();
	BOOL m_bFir;
	CSpectData *m_pSpData;
	CPage1(CWnd* pParent = NULL);   // standard constructor

	DECLARE_DYNCREATE(CPage1)

// Dialog Data
	//{{AFX_DATA(CPage1)
	enum { IDD = IDD_PAGE1 };
	CDrawForMySpec	m_cSDCM;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPage1)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE1_H__ED9FC462_9CA1_11DB_949D_00055D02EEF1__INCLUDED_)
