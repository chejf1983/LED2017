#if !defined(AFX_ADDUSERSDLG_H__6E70BADE_A168_43FD_8C8D_BF67DE314337__INCLUDED_)
#define AFX_ADDUSERSDLG_H__6E70BADE_A168_43FD_8C8D_BF67DE314337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddUsersDlg.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
/////////////////////////////////////////////////////////////////////////////
// CAddUsersDlg dialog

class CAddUsersDlg : public CResizingDialog
{
// Construction
public:
	CAddUsersDlg(CWnd* pParent = NULL);   // standard constructor
	void SetDialogFace();
// Dialog Data
	//{{AFX_DATA(CAddUsersDlg)
	enum { IDD = IDD_AddUsersDlg };
	CBitButtonNL m_addexit;
	CBitButtonNL m_addsure;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddUsersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddUsersDlg)
	afx_msg void OnExit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg bool OnSure();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDUSERSDLG_H__6E70BADE_A168_43FD_8C8D_BF67DE314337__INCLUDED_)
