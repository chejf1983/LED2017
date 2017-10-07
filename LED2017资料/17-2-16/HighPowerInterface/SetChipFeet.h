#if !defined(AFX_SETCHIPFEET_H__E3CC77DE_289B_457F_BC15_0596D5D5ACB9__INCLUDED_)
#define AFX_SETCHIPFEET_H__E3CC77DE_289B_457F_BC15_0596D5D5ACB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetChipFeet.h : header file
//

#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
#include "ChipType.h"
/////////////////////////////////////////////////////////////////////////////
// CSetChipFeet dialog

class CSetChipFeet : public CResizingDialog
{
// Construction
public:
	CSetChipFeet(CWnd* pParent = NULL);   // standard constructor
	CChipType m_chiptypedlg;

	int tempWLType; 
	int tempCommonfoot;
// Dialog Data
	//{{AFX_DATA(CSetChipFeet)
	enum { IDD = IDD_SetChipFeet };
	CBitButtonNL	m_ChipsType;
	CBitButtonNL	m_MiddleWave2;
	CBitButtonNL	m_MiddleWave1;
	CComboBox	m_packageway;
	CComboBox	m_commonfoot;
	CBitButtonNL	m_Showchip;
	CComboBox	m_wltype;
	CComboBox	m_polarity;
	CComboBox	m_chiptype;
	int		m_setway;
	//}}AFX_DATA
	void InitBitmap();
	void getParameter(); 
	void SetDialogFace();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetChipFeet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetChipFeet)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnGetMiddleWave1();
	afx_msg void OnGetMiddleWave2();
	afx_msg void OnSetwayIF();
	afx_msg void OnSetwayIV();
	afx_msg void OnSetwayWL();
	afx_msg void OnFigureChipstyle();
	afx_msg void OnSelectchip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETCHIPFEET_H__E3CC77DE_289B_457F_BC15_0596D5D5ACB9__INCLUDED_)
