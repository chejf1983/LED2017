#if !defined(AFX_DLGSELECT_H__B8B65E61_886A_11D8_A0D0_00055D02EEF1__INCLUDED_)
#define AFX_DLGSELECT_H__B8B65E61_886A_11D8_A0D0_00055D02EEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSeleCT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSeleCT dialog

class CDlgSeleCT : public CDialog
{
// Construction
public:
	int m_iN;
	int m_iSele;
	CDlgSeleCT(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSeleCT)
	enum { IDD = IDD_SELE_CT };
	CListBox	m_cList;
	int		m_iSDCM1;
	int		m_iSDCM2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSeleCT)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSeleCT)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDeltaposSpin5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELECT_H__B8B65E61_886A_11D8_A0D0_00055D02EEF1__INCLUDED_)
