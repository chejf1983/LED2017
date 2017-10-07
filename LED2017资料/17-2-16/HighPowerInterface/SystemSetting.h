#if !defined(AFX_SYSTEMSETTING_H__B677418B_7AC0_4F49_8849_CDD0C5981D03__INCLUDED_)
#define AFX_SYSTEMSETTING_H__B677418B_7AC0_4F49_8849_CDD0C5981D03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SystemSetting.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
/////////////////////////////////////////////////////////////////////////////
// CSystemSetting dialog

class CSystemSetting : public CResizingDialog
{
// Construction
public:
	CSystemSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSystemSetting)
	enum { IDD = IDD_SystemSetting };
	CBitButtonNL	m_exit;
	CBitButtonNL	m_ElecTest;
	CBitButtonNL	m_OOIConfig;
	CBitButtonNL	m_systemsave;
	//}}AFX_DATA

	void SetDialogFace();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSystemSetting)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg bool OnSystemSave();
	afx_msg void OnCheckHardware();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnOOIConfig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMSETTING_H__B677418B_7AC0_4F49_8849_CDD0C5981D03__INCLUDED_)
