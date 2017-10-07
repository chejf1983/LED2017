#if !defined(AFX_DLGLEDCLASSDATAEDIT_H__B9911A51_9FDB_4EE0_A0C0_0835ADFA34B1__INCLUDED_)
#define AFX_DLGLEDCLASSDATAEDIT_H__B9911A51_9FDB_4EE0_A0C0_0835ADFA34B1__INCLUDED_

#include "LimitData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLEDClassDataEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLEDClassDataEdit dialog

class CDlgLEDClassDataEdit : public CDialog
{
// Construction
public:
	CDlgLEDClassDataEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLEDClassDataEdit)
	enum { IDD = IDD_LED_CLASS_DATA_EDIT };
	CStatic	m_cColor;
	CButton	m_cMod;
	CEdit	m_cD2;
	CEdit	m_cD1;
	CListBox	m_cList;
	float	m_fD1;
	float	m_fD2;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLEDClassDataEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLEDClassDataEdit)
	afx_msg void OnButtonMod();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSelchangeList();
	afx_msg void OnChangeEditName();
	afx_msg void OnColor();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	COLORREF m_color;
	CArray<int,int>     m_iListType;

	CArray<float,float> m_fLimit1;
	CArray<float,float> m_fLimit2;
private:
	BOOL m_bMod;
	void ReList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLEDCLASSDATAEDIT_H__B9911A51_9FDB_4EE0_A0C0_0835ADFA34B1__INCLUDED_)
