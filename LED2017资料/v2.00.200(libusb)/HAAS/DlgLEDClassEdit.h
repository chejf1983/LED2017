#if !defined(AFX_DLGLEDCLASSEDIT_H__D1E358AC_F137_42F7_BDF8_411632314325__INCLUDED_)
#define AFX_DLGLEDCLASSEDIT_H__D1E358AC_F137_42F7_BDF8_411632314325__INCLUDED_

#include "NewLEDClass.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLEDClassEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLEDClassEdit dialog

class CDlgLEDClassEdit : public CDialog
{
// Construction
public:
	CString m_strPathName;
	int m_iSele;
	CDlgLEDClassEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLEDClassEdit)
	enum { IDD = IDD_LED_CLASS_EDIT };
	CListCtrl	m_cList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLEDClassEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLEDClassEdit)
	virtual void OnOK();
	afx_msg void OnButtonSet();
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDel();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonMod();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonExport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bMod;
	CNewLEDClass m_classData;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLEDCLASSEDIT_H__D1E358AC_F137_42F7_BDF8_411632314325__INCLUDED_)
