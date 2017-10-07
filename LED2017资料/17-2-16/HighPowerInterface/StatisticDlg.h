#if !defined(AFX_STATISTICDLG_H__79D9565E_A699_4FED_BCCC_94B1EE664CC1__INCLUDED_)
#define AFX_STATISTICDLG_H__79D9565E_A699_4FED_BCCC_94B1EE664CC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatisticDlg.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\ReDrawListCtrl\ComboListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CStatisticDlg dialog

class CStatisticDlg : public CResizingDialog
{
// Construction
public:
	CStatisticDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatisticDlg)
	enum { IDD = IDD_Statistic };
	CComboListCtrl	m_statistic_list;
	//}}AFX_DATA
	void Initstatistics();
	void Savestatistics();
	void ShowResults();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatisticDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatisticDlg)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATISTICDLG_H__79D9565E_A699_4FED_BCCC_94B1EE664CC1__INCLUDED_)
