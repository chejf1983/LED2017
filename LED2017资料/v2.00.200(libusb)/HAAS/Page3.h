#if !defined(AFX_PAGE3_H__FC741761_9FC2_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_PAGE3_H__FC741761_9FC2_11DB_949D_00055D02EEF1__INCLUDED_

#include "DrawForMySpec.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage3 dialog

class CPage3 : public CDialog
{
// Construction
public:
	void SaveSet();
	DATA_DRAW m_drawData;
	void ReDraw();
	BOOL m_bFir;
	CSpectData *m_pSpData;
	void SetPos();
	CPage3(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPage3)
	enum { IDD = IDD_PAGE3 };
	CButton	m_cRR;
	CButton	m_cR;
	CButton	m_cLL;
	CButton	m_cL;
	CDrawForMySpec	m_cDraw;
	BOOL	m_bShowCur;
	//}}AFX_DATA
	DECLARE_DYNCREATE(CPage3)


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPage3)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKickIdle();
	afx_msg void OnCheckCur();
	afx_msg void OnButtonLl();
	afx_msg void OnButtonL();
	afx_msg void OnButtonR();
	afx_msg void OnButtonRr();
	afx_msg void OnButtonType();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE3_H__FC741761_9FC2_11DB_949D_00055D02EEF1__INCLUDED_)
