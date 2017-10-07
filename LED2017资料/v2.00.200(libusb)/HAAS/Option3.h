#if !defined(AFX_OPTION3_H__E4CBA63E_E812_4EC2_9C08_889CF40B6F73__INCLUDED_)
#define AFX_OPTION3_H__E4CBA63E_E812_4EC2_9C08_889CF40B6F73__INCLUDED_

#include "DrawForMySpec.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Option3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COption3 dialog

class COption3 : public CPropertyPage
{
	DECLARE_DYNCREATE(COption3)

// Construction
public:
	COption3();
	~COption3();

// Dialog Data
	//{{AFX_DATA(COption3)
	enum { IDD = IDD_OPTION3 };
	CDrawForMySpec	m_cBK;
	CDrawForMySpec	m_cText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COption3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COption3)
	afx_msg void OnButtonSeleText();
	afx_msg void OnButtonSeleBk();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTION3_H__E4CBA63E_E812_4EC2_9C08_889CF40B6F73__INCLUDED_)
