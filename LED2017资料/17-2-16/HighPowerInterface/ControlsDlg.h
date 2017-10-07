#if !defined(AFX_CONTROLSDLG_H__51D7FBD2_8EA0_4344_BFD3_4DEFA9DA7E5F__INCLUDED_)
#define AFX_CONTROLSDLG_H__51D7FBD2_8EA0_4344_BFD3_4DEFA9DA7E5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ControlsDlg.h : header file
//

#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
#include "ReDrawEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CControlsDlg dialog

class CControlsDlg : public CResizingDialog
{
// Construction
public:
	CControlsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CControlsDlg)
	enum { IDD = IDD_Controls };
	CReDrawEdit	m_EditTotal;
	CButton	m_showsetting;
	CBitButtonNL	m_minusdark;
	CBitButtonNL	m_single;
	CBitButtonNL	m_retest;
	CBitButtonNL	m_continue;
	CBitButtonNL	m_auto;
	CBitButtonNL	m_stop;
	//}}AFX_DATA
	void ShowResults(int total, int pass);
	void Savepasspercent();
	void SetDialogFace();
	void SetDialogFace2();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlsDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CControlsDlg)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC); 
	afx_msg void OnSingle();
	afx_msg void OnContinuous();
	afx_msg void OnRetest();
	afx_msg void OnMinusDark();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStoptest();
	afx_msg void OnAuto();
	afx_msg void OnButton6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLSDLG_H__51D7FBD2_8EA0_4344_BFD3_4DEFA9DA7E5F__INCLUDED_)
