#if !defined(AFX_DLGSETHAAS_H__6E8A2619_34AF_4623_91CF_7268B563B9EA__INCLUDED_)
#define AFX_DLGSETHAAS_H__6E8A2619_34AF_4623_91CF_7268B563B9EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetHaas.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetHaas dialog

class CDlgSetHaas : public CDialog
{
// Construction
public:
	CDlgSetHaas(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetHaas)
	enum { IDD = IDD_SET_HAAS };
	CComboBox	m_cMode;
	CComboBox	m_cBin;
	int		m_iBin;
	int		m_iMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetHaas)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetHaas)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETHAAS_H__6E8A2619_34AF_4623_91CF_7268B563B9EA__INCLUDED_)
