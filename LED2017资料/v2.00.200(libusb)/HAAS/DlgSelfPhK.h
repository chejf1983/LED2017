#if !defined(AFX_DLGSELFPHK_H__743A96F5_818A_4415_B1F4_8F00B8A79585__INCLUDED_)
#define AFX_DLGSELFPHK_H__743A96F5_818A_4415_B1F4_8F00B8A79585__INCLUDED_

#include "SpectData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelfPhK.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSelfPhK dialog

class CDlgSelfPhK : public CDialog
{
// Construction
public:
	CSpectData m_spData;

	void CalcPhK();
	BOOL GetPh(float &fPh);
	CDlgSelfPhK(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSelfPhK)
	enum { IDD = IDD_SELF_PH_K };
	CButton	m_cSave;
	CButton	m_cSele;
	CEdit	m_cSelfPhK;
	CEdit	m_cPh2;
	CEdit	m_cPh1;
	CEdit	m_cPhK;
	float	m_fSelfPhK;
	int		m_iType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelfPhK)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSelfPhK)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonTest1();
	afx_msg void OnButtonTest2();
	afx_msg void OnSelchangeComboType();
	afx_msg void OnButtonSele();
	afx_msg void OnButtonSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELFPHK_H__743A96F5_818A_4415_B1F4_8F00B8A79585__INCLUDED_)
