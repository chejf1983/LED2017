#if !defined(AFX_BINDLG_H__61221A92_1CD2_40BC_AEFA_E144F525BCE9__INCLUDED_)
#define AFX_BINDLG_H__61221A92_1CD2_40BC_AEFA_E144F525BCE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BinDlg.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\ReDrawListCtrl\ComboListCtrl.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
/////////////////////////////////////////////////////////////////////////////
// CBinDlg dialog

class CBinDlg : public CResizingDialog
{
// Construction
public:
	CBinDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBinDlg)
	enum { IDD = IDD_Bin };
	CBitButtonNL	m_BinNum;
	CComboListCtrl	m_bin_list;
	//}}AFX_DATA
//	CString databuffer[3][500];
	void Initbin();
	void Savebin();
	void ShowResults();
	void UpdateData(int bin);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBinDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBinDlg)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnGetdispinfoBinList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOdcachehintBinList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOdfinditemBinList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINDLG_H__61221A92_1CD2_40BC_AEFA_E144F525BCE9__INCLUDED_)
