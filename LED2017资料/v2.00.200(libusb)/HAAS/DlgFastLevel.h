#if !defined(AFX_DLGFASTLEVEL_H__62D6FC84_37D1_11DA_ABAD_00055D02EEF1__INCLUDED_)
#define AFX_DLGFASTLEVEL_H__62D6FC84_37D1_11DA_ABAD_00055D02EEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFastLevel.h : header file
//

#include "LevelLimit.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgFastLevel dialog

class CDlgFastLevel : public CDialog
{
// Construction
public:
	void Insert();

	int   m_iCur;
	float m_fLevel1[10];
	float m_fLevel2[10];

	CDlgFastLevel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFastLevel)
	enum { IDD = IDD_FAST_LEVEL };
	CEdit	m_cN;
	CStatic	m_cS2;
	CStatic	m_cS1;
	CListBox	m_cList;
	int		m_iN;
	CString	m_strName;
	float	m_fData1;
	float	m_fData2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFastLevel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFastLevel)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditN();
	virtual void OnOK();
	afx_msg void OnButtonSavedata();
	afx_msg void OnButtonMod();
	virtual void OnCancel();
	afx_msg void OnSelchangeList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFASTLEVEL_H__62D6FC84_37D1_11DA_ABAD_00055D02EEF1__INCLUDED_)
