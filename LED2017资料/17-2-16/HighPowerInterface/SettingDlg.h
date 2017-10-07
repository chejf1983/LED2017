#if !defined(AFX_SETTINGDLG_H__B1B984A2_A1CF_4377_85F6_6DD9FA9964AA__INCLUDED_)
#define AFX_SETTINGDLG_H__B1B984A2_A1CF_4377_85F6_6DD9FA9964AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
#include "RedrawTabCtrl.h"
#include "SetParameter.h"
#include "LevelDlg.h"
#include "ShowTestDlg.h"
#include "SetChipFeet.h"
/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog

class CSettingDlg : public CResizingDialog
{
// Construction
public:
	CSettingDlg(CWnd* pParent = NULL);   // standard constructor
	CSetParameter m_setparameter;
	CLevelDlg m_leveldlg;
	CSetChipFeet m_chipfeet;
	int m_CurSelTab;
	CDialog* pDialog[3];  //用来保存对话框对象指针
// Dialog Data
	//{{AFX_DATA(CSettingDlg)
	enum { IDD = IDD_Setting };
	CBitButtonNL	m_exit;
	CBitButtonNL	m_authority;
	CBitButtonNL	m_saveset;
	CRedrawTabCtrl	m_settingtab;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	bool initTempItem();
	void SetDialogFace();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingDlg)
	afx_msg void OnExit();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeSettingTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSaveSetting();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnAuthority();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG_H__B1B984A2_A1CF_4377_85F6_6DD9FA9964AA__INCLUDED_)
