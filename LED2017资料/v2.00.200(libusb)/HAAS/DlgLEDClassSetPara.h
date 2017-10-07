#if !defined(AFX_DLGLEDCLASSSETPARA_H__236FADD7_B1FE_4EAB_851F_3B8DF8920071__INCLUDED_)
#define AFX_DLGLEDCLASSSETPARA_H__236FADD7_B1FE_4EAB_851F_3B8DF8920071__INCLUDED_

#include "NewLEDClass.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLEDClassSetPara.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLEDClassSetPara dialog

class CDlgLEDClassSetPara : public CDialog
{
// Construction
public:
	CDlgLEDClassSetPara(CWnd* pParent = NULL);   // standard constructor

	CNewLEDClass *m_pClassData;

// Dialog Data
	//{{AFX_DATA(CDlgLEDClassSetPara)
	enum { IDD = IDD_LED_CLASS_SET_PARA };
	CListBox	m_cList;
	CComboBox	m_cType;
	int		m_iType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLEDClassSetPara)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLEDClassSetPara)
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDel();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CArray<int,int> m_iListType;
	CArray<CString,CString> m_strListName;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLEDCLASSSETPARA_H__236FADD7_B1FE_4EAB_851F_3B8DF8920071__INCLUDED_)
