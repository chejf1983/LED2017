#if !defined(AFX_SETSPMSAVEDARK_H__9057831E_B51A_4920_AF4A_01B2C454B430__INCLUDED_)
#define AFX_SETSPMSAVEDARK_H__9057831E_B51A_4920_AF4A_01B2C454B430__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSpmSaveDark.h : header file
//
#include "resFile\BitButtonNL/BitButtonNL.h"
/////////////////////////////////////////////////////////////////////////////
// CSetSpmSaveDark dialog

class CSetSpmSaveDark : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetSpmSaveDark)

// Construction
public:
	CSetSpmSaveDark();
	~CSetSpmSaveDark();

	bool savedark;
	CWnd *pWnd_picture; 
	CDC *pDC_picture;
	RECT Dark_rect; 
// Dialog Data
	//{{AFX_DATA(CSetSpmSaveDark)
	enum { IDD = IDD_SetSpmSaveDark };
	CButton	m_saveas;
	CBitButtonNL m_saveDark;
	//}}AFX_DATA
	void getSpectrumDark();

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetSpmSaveDark)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	virtual BOOL OnQueryCancel();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetSpmSaveDark)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnScanFile();
	afx_msg void OnSaveDark();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSaveAsSpec();
	afx_msg void OnEnlarge();
	afx_msg void OnSmaller();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETSPMSAVEDARK_H__9057831E_B51A_4920_AF4A_01B2C454B430__INCLUDED_)
