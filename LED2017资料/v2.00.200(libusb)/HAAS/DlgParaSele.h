#if !defined(AFX_DLGPARASELE_H__97EABDA5_2F59_11DB_949C_00055D02EEF1__INCLUDED_)
#define AFX_DLGPARASELE_H__97EABDA5_2F59_11DB_949C_00055D02EEF1__INCLUDED_

#include <afxtempl.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgParaSele.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgParaSele dialog

class CDlgParaSele : public CDialog
{
// Construction
public:
	CArray<CString,CString> m_arraName ;
	CDlgParaSele(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgParaSele)
	enum { IDD = IDD_PARA_SELE };
	CComboBox	m_cName;
	int		m_iName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgParaSele)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgParaSele)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPARASELE_H__97EABDA5_2F59_11DB_949C_00055D02EEF1__INCLUDED_)
