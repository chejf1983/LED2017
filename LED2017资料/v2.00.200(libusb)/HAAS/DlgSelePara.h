#if !defined(AFX_DLGSELEPARA_H__C286E6E1_05B2_11DB_949C_00055D02EEF1__INCLUDED_)
#define AFX_DLGSELEPARA_H__C286E6E1_05B2_11DB_949C_00055D02EEF1__INCLUDED_

#include "DrawForMySpec.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelePara.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSelePara dialog

class CDlgSelePara : public CDialog
{
// Construction
public:
	COLORREF m_refC;
	int m_iPara;
	int m_iN;
	int m_iList[100];
	CDlgSelePara(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSelePara)
	enum { IDD = IDD_SELE_PARA };
	CListBox	m_cList;
	CDrawForMySpec	m_cC;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelePara)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSelePara)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnC();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELEPARA_H__C286E6E1_05B2_11DB_949C_00055D02EEF1__INCLUDED_)
