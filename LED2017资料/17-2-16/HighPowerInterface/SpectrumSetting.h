#if !defined(AFX_SPECTRUMSETTING_H__457C378A_2C6E_46C8_B786_1F1F7B9D4334__INCLUDED_)
#define AFX_SPECTRUMSETTING_H__457C378A_2C6E_46C8_B786_1F1F7B9D4334__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpectrumSetting.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
/////////////////////////////////////////////////////////////////////////////
// CSpectrumSetting dialog

class CSpectrumSetting : public CResizingDialog
{
// Construction
public:
	CSpectrumSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSpectrumSetting)
	enum { IDD = IDD_SpectrumSetting };
	CBitButtonNL	m_getSpecParam;
	CBitButtonNL	m_exit;
	CBitButtonNL	m_spectrumset;
	//}}AFX_DATA

	void SetDialogFace();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpectrumSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpectrumSetting)
	afx_msg void OnExit();
	afx_msg void OnSpectrumSet();
	virtual BOOL OnInitDialog();
	afx_msg void OngetSpectraPara();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECTRUMSETTING_H__457C378A_2C6E_46C8_B786_1F1F7B9D4334__INCLUDED_)
