#if !defined(AFX_LEVELDLG_H__71AD9F3E_74CE_42B9_9D75_197EFEDB1C31__INCLUDED_)
#define AFX_LEVELDLG_H__71AD9F3E_74CE_42B9_9D75_197EFEDB1C31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LevelDlg.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\ReDrawListCtrl\ComboListCtrl.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
#include "resFile\PopMenu\popupmenu.h"
#include "AccumulateLevel.h"

#define LEVELCOLUMNS 102
/////////////////////////////////////////////////////////////////////////////
// CLevelDlg dialog
class CLevelDlg : public CResizingDialog
{
// Construction
public:
	CLevelDlg(CWnd* pParent = NULL);   // standard constructor
	CMenu m_menu;
	int cols[3];
// Dialog Data
	//{{AFX_DATA(CLevelDlg)
	enum { IDD = IDD_Level };
	CBitButtonNL	m_levelFile;
	CBitButtonNL	m_handleLevel;
	CComboListCtrl	m_levellist;
	//}}AFX_DATA
	bool insertIteminit(CString text);
	bool initdlg(CString (*string)[LEVELCOLUMNS], bool level);
	bool updateLevelList();
	bool updateLevelList2();
	void getParameter();
	void getParameter2();
	int CalculateLevelNum(int column, int colsnum);
	void SetDialogFace();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLevelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLevelDlg)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void Onlevelfile();
	afx_msg void OnExportlevelfile();
	afx_msg void OnInportlevelfile();
	afx_msg void OnSavelevelfile();
	afx_msg void OnHandlelevel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClearBinCode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEVELDLG_H__71AD9F3E_74CE_42B9_9D75_197EFEDB1C31__INCLUDED_)
