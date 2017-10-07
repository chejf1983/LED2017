#if !defined(AFX_SETSPMCOMPEN_H__53F43CFF_C80E_4A1B_B1D9_BFDE6978C719__INCLUDED_)
#define AFX_SETSPMCOMPEN_H__53F43CFF_C80E_4A1B_B1D9_BFDE6978C719__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSpmCompen.h : header file
//
#include "resFile\ReDrawListCtrl\ComboListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CSetSpmCompen dialog

class CSetSpmCompen : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetSpmCompen)

// Construction
public:
	CSetSpmCompen();
	~CSetSpmCompen();

	CWnd *pWnd_picture; 
	CDC *pDC_picture;
	RECT rect; 	
// Dialog Data
	//{{AFX_DATA(CSetSpmCompen)
	enum { IDD = IDD_SetSpmCompen };
	CComboListCtrl	m_compenlist;
	int		m_areaway;
	//}}AFX_DATA

	void SetList();
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetSpmCompen)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetSpmCompen)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSaveAs();
	afx_msg void OnAreaWay0();
	afx_msg void OnAreaWay1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETSPMCOMPEN_H__53F43CFF_C80E_4A1B_B1D9_BFDE6978C719__INCLUDED_)
