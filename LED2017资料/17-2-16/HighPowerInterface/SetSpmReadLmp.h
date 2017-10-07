#if !defined(AFX_SETSPMREADLMP_H__8260DD31_F903_47F2_97F5_27BB6A034C23__INCLUDED_)
#define AFX_SETSPMREADLMP_H__8260DD31_F903_47F2_97F5_27BB6A034C23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSpmReadLmp.h : header file
//
#include "resFile\ReDrawListCtrl\ComboListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CSetSpmReadLmp dialog

class CSetSpmReadLmp : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetSpmReadLmp)

// Construction
public:
	CSetSpmReadLmp();
	~CSetSpmReadLmp();

	CWnd *pWnd_picture; 
	CDC *pDC_picture;
	RECT rect; 	

	bool openlmp;
// Dialog Data
	//{{AFX_DATA(CSetSpmReadLmp)
	enum { IDD = IDD_SetSpmReadLmp };
	CComboListCtrl	m_lmplist;
	//}}AFX_DATA

	BOOL CalWavePower(double *wl); 
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetSpmReadLmp)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetSpmReadLmp)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnOpenLmpFile();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	void SetList();
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETSPMREADLMP_H__8260DD31_F903_47F2_97F5_27BB6A034C23__INCLUDED_)
