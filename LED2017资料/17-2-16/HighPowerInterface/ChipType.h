#if !defined(AFX_CHIPTYPE_H__FC340CFA_52B0_4E41_B28D_33FF003BAE47__INCLUDED_)
#define AFX_CHIPTYPE_H__FC340CFA_52B0_4E41_B28D_33FF003BAE47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChipType.h : header file
//

#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
/////////////////////////////////////////////////////////////////////////////
// CChipType dialog

class CChipType : public CResizingDialog
{
// Construction
public:
	CChipType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChipType)
	enum { IDD = IDD_ChipType };
	CBitButtonNL	m_type17;
	CBitButtonNL	m_type16;
	CBitButtonNL	m_type15;
	CBitButtonNL	m_type14;
	CBitButtonNL	m_type13;
	CBitButtonNL	m_type12;
	CBitButtonNL	m_type11;
	CBitButtonNL	m_type10;
	CBitButtonNL	m_type9;
	CBitButtonNL	m_type8;
	CBitButtonNL	m_type7;
	CBitButtonNL	m_type6;
	CBitButtonNL	m_type5;
	CBitButtonNL	m_type4;
	CBitButtonNL	m_type3;
	CBitButtonNL	m_type2;
	CBitButtonNL	m_type1;
	CBitButtonNL	m_type0;
	//}}AFX_DATA
	void InitButton();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChipType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChipType)
	virtual BOOL OnInitDialog();
	afx_msg void Ontype0();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void Ontype1();
	afx_msg void Ontype2();
	afx_msg void Ontype3();
	afx_msg void Ontype4();
	afx_msg void Ontype5();
	afx_msg void Ontype6();
	afx_msg void Ontype7();
	afx_msg void Ontype8();
	afx_msg void Ontype9();
	afx_msg void Ontype10();
	afx_msg void Ontype11();
	afx_msg void Ontype12();
	afx_msg void Ontype13();
	afx_msg void Ontype14();
	afx_msg void Ontype15();
	afx_msg void Ontype16();
	afx_msg void Ontype17();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHIPTYPE_H__FC340CFA_52B0_4E41_B28D_33FF003BAE47__INCLUDED_)
