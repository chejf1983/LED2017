#if !defined(AFX_SETUP5_H__C77C7E39_138D_4558_B8F2_DB435E95B170__INCLUDED_)
#define AFX_SETUP5_H__C77C7E39_138D_4558_B8F2_DB435E95B170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Setup5.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetup5 dialog

class CSetup5 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetup5)

// Construction
public:
	void EnableShow();
	CSetup5();
	~CSetup5();

// Dialog Data
	//{{AFX_DATA(CSetup5)
	enum { IDD = IDD_SETUP5 };
	CEdit	m_cCurrTMP;
	BOOL	m_bHaveUseLEDTMP;
	float	m_fSetTMP;
	CString	m_strLEDTMPCom;
	int		m_iType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetup5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetup5)
	afx_msg void OnCheckUseLedTmp();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonReadTmp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUP5_H__C77C7E39_138D_4558_B8F2_DB435E95B170__INCLUDED_)
