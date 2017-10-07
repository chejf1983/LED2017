#if !defined(AFX_SETUP4_H__A24AFFBA_A7D6_46B3_8BF7_10C5BAA1A1DE__INCLUDED_)
#define AFX_SETUP4_H__A24AFFBA_A7D6_46B3_8BF7_10C5BAA1A1DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Setup4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetup4 dialog

class CSetup4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetup4)

// Construction
public:
	int  m_iCur;
	void ReList();
	CSetup4();
	~CSetup4();

// Dialog Data
	//{{AFX_DATA(CSetup4)
	enum { IDD = IDD_SETUP4 };
	CListCtrl	m_cList;
	CButton	m_cSetOk;
	CButton	m_cSet;
	int		m_iNum;
	int		m_iT;
	BOOL	m_bCheckTimeTest;
	BOOL	m_bSame;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetup4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetup4)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSetOk();
	afx_msg void OnButtonSet();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditNum();
	afx_msg void OnChangeEditT();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUP4_H__A24AFFBA_A7D6_46B3_8BF7_10C5BAA1A1DE__INCLUDED_)
