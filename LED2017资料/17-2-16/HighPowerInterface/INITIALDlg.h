#if !defined(AFX_INITIALDLG_H__43E4F8F1_B9BA_4C47_A76B_F231EF1DAC54__INCLUDED_)
#define AFX_INITIALDLG_H__43E4F8F1_B9BA_4C47_A76B_F231EF1DAC54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// INITIALDlg.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
#include "resFile\Progress\MacProgressCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CINITIALDlg dialog

class CINITIALDlg : public CResizingDialog
{
// Construction
public:
	CINITIALDlg(CWnd* pParent = NULL);   // standard constructor
	bool inisuccess;
	bool cancel;
// Dialog Data
	//{{AFX_DATA(CINITIALDlg)
	enum { IDD = IDD_INITIAL };
	CBitButtonNL	m_cancel;
	CBitButtonNL	m_iniAll;
	CBitButtonNL	m_leftTime;
	CBitButtonNL  m_showprogress;
	CMacProgressCtrl	m_progress;
	int		m_spectrumstyle;
	//}}AFX_DATA

	void SetDialogFace();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CINITIALDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CINITIALDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OniniAll();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnCancel();
	afx_msg void OnSelUSB2000();
	afx_msg void OnSelPC2000();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INITIALDLG_H__43E4F8F1_B9BA_4C47_A76B_F231EF1DAC54__INCLUDED_)
