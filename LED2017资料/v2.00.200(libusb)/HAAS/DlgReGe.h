#if !defined(AFX_DLGREGE_H__D2FA2D0A_E7E4_4A86_87CC_3B6A8B2E2DBF__INCLUDED_)
#define AFX_DLGREGE_H__D2FA2D0A_E7E4_4A86_87CC_3B6A8B2E2DBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgReGe.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgReGe dialog

class CDlgReGe : public CDialog
{
// Construction
public:
	CDlgReGe(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgReGe)
	enum { IDD = IDD_DIALOG_RE_CAL_GE };
	float	m_fGeWL1;
	float	m_fGeWL2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgReGe)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgReGe)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREGE_H__D2FA2D0A_E7E4_4A86_87CC_3B6A8B2E2DBF__INCLUDED_)
