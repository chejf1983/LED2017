#if !defined(AFX_SETPRINT_H__8822301F_FEA5_48A6_A2E0_DF7671E2FCAF__INCLUDED_)
#define AFX_SETPRINT_H__8822301F_FEA5_48A6_A2E0_DF7671E2FCAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetPrint.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\ReDrawListCtrl\ComboListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CSetPrint dialog

class CSetPrint : public CResizingDialog
{
// Construction
public:
	CSetPrint(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetPrint)
	enum { IDD = IDD_SetPrint };
	CComboBox	m_selectItem;
	CComboListCtrl	m_printlist;
	CComboBox	m_printMode;
	CComboBox	m_itemCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetPrint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetPrint)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnprintForm();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSave();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeselectItem();
	afx_msg void OnSelchangeItemCode();
	afx_msg void OnclearSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	bool InitSelectItem();
	bool InitPrintList();
	bool InitPrintSet();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETPRINT_H__8822301F_FEA5_48A6_A2E0_DF7671E2FCAF__INCLUDED_)
