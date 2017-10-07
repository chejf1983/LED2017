#if !defined(AFX_SETSPMSAVEREFER_H__1873E70D_FFF6_454B_9437_2717828B9112__INCLUDED_)
#define AFX_SETSPMSAVEREFER_H__1873E70D_FFF6_454B_9437_2717828B9112__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSpmSaveRefer.h : header file
//
#include "resFile\BitButtonNL/BitButtonNL.h"
/////////////////////////////////////////////////////////////////////////////
// CSetSpmSaveRefer dialog

class CSetSpmSaveRefer : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetSpmSaveRefer)

// Construction
public:
	CSetSpmSaveRefer();
	~CSetSpmSaveRefer();

	bool saverefer;
	CWnd *pWnd_picture; 
	CDC *pDC_picture;
	RECT Refer_rect; 
// Dialog Data
	//{{AFX_DATA(CSetSpmSaveRefer)
	enum { IDD = IDD_SetSpmSaveRefer };
	CButton	m_saveas;
	CBitButtonNL m_saveRefer;
	//}}AFX_DATA
	void getSpectrumRefer();

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetSpmSaveRefer)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnQueryCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetSpmSaveRefer)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnScanFile();
	afx_msg void OnSaveRefer();
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

#endif // !defined(AFX_SETSPMSAVEREFER_H__1873E70D_FFF6_454B_9437_2717828B9112__INCLUDED_)
