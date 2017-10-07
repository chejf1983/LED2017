#if !defined(AFX_SHOWTESTDLG_H__1FF6D6EB_FA8E_456C_B5FE_7B1D1217DFAC__INCLUDED_)
#define AFX_SHOWTESTDLG_H__1FF6D6EB_FA8E_456C_B5FE_7B1D1217DFAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowTestDlg.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\ReDrawListCtrl\ComboListCtrl.h"
#include "ShowTestPopup.h"
/////////////////////////////////////////////////////////////////////////////
// CShowTestDlg dialog

class CShowTestDlg : public CResizingDialog
{
// Construction
public:
	CShowTestDlg(CWnd* pParent = NULL);   // standard constructor
	ShowTestPopup m_popupshow;
	CArray <CString, CString> databuffer[50];
	CString settingbuffer[6][50];
// Dialog Data
	//{{AFX_DATA(CShowTestDlg)
	enum { IDD = IDD_ShowTest };
	CButton	m_maxmin;
	CComboListCtrl	m_showtest_list;
	//}}AFX_DATA
	void Initshowtest();
	void Saveshowtest();
	void ShowResults(int chip, int line, int bin);
	void ShowSetting(int chip, int count);
	void ShowNULL(int chip, int line, int bin);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowTestDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnGetdispinfoShowTestList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOdfinditemShowTestList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOdcachehintShowTestList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWTESTDLG_H__1FF6D6EB_FA8E_456C_B5FE_7B1D1217DFAC__INCLUDED_)
