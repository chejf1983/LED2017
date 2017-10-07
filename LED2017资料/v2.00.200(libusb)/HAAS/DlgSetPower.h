#if !defined(AFX_DLGSETPOWER_H__CE44A842_9A8A_11D8_A0D0_00055D02EEF1__INCLUDED_)
#define AFX_DLGSETPOWER_H__CE44A842_9A8A_11D8_A0D0_00055D02EEF1__INCLUDED_

#include "WYDlg.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetPower.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetPower dialog

class CDlgSetPower : public CDialog
{
// Construction
public:
	CWYDlg *pDlg;
	CWinThread *Thread;
	CString m_strVol,m_strCurr;
	float m_fVol,m_fCurr;
	int m_iR;
	CDlgSetPower(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetPower)
	enum { IDD = IDD_SET_POWER };
	CButton	m_cCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetPower)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetPower)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSetClose(UINT wParam, LONG lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETPOWER_H__CE44A842_9A8A_11D8_A0D0_00055D02EEF1__INCLUDED_)
