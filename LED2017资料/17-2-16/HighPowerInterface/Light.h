#if !defined(AFX_LIGHT_H__4367D9DC_F58E_4BCB_87D8_A08D1213B1A5__INCLUDED_)
#define AFX_LIGHT_H__4367D9DC_F58E_4BCB_87D8_A08D1213B1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Light.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
/////////////////////////////////////////////////////////////////////////////
// CLight dialog

class CLight : public CResizingDialog
{
// Construction
public:
	CLight(CWnd* pParent = NULL);   // standard constructor
	int chip;
	double voltage;
	double current;
	CString str;
// Dialog Data
	//{{AFX_DATA(CLight)
	enum { IDD = IDD_Light };
	CBitButtonNL	m_lightOn;
	CBitButtonNL	m_lightOff;
	CBitButtonNL	m_cancel;
	CComboBox	m_chipType;
	//}}AFX_DATA

	void SetDialogFace();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLight)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLight)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLightOn();
	afx_msg void OnLightOff();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHT_H__4367D9DC_F58E_4BCB_87D8_A08D1213B1A5__INCLUDED_)
