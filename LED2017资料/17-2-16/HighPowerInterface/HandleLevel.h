#if !defined(AFX_HANDLELEVEL_H__B2DF1D0C_4653_4FE5_919A_FBB987E1B4FB__INCLUDED_)
#define AFX_HANDLELEVEL_H__B2DF1D0C_4653_4FE5_919A_FBB987E1B4FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HandleLevel.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
#include "ReDrawEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CHandleLevel dialog

class CHandleLevel : public CResizingDialog
{
// Construction
public:
	CHandleLevel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHandleLevel)
	enum { IDD = IDD_HandleLevel };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHandleLevel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHandleLevel)
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HANDLELEVEL_H__B2DF1D0C_4653_4FE5_919A_FBB987E1B4FB__INCLUDED_)
