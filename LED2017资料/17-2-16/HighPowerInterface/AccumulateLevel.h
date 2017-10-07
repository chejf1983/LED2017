#if !defined(AFX_ACCUMULATELEVEL_H__E22D5BAC_3D93_47CD_A6CE_2F451D607571__INCLUDED_)
#define AFX_ACCUMULATELEVEL_H__E22D5BAC_3D93_47CD_A6CE_2F451D607571__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AccumulateLevel.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
#include "resFile\ReDrawListCtrl\ComboListCtrl.h"
#include "resFile\PopMenu\popupmenu.h"
/////////////////////////////////////////////////////////////////////////////
// CAccumulateLevel dialog
typedef struct
{
	CString AccuItem;
	int way;
	double base;
	double step;
	int levelnum;

}TempAccuItem;

typedef struct
{
	CString item;
	int levelnum;
	CString bincode[300];
	double max[300];
	double min[300];
	double x[300][4];
	double y[300][4];

}LevelItem;

class CAccumulateLevel : public CResizingDialog
{
// Construction
public:
	CAccumulateLevel(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CAccumulateLevel)
	enum { IDD = IDD_AccumulateLevel };
	CComboBox	m_delway;
	CButton	m_shootcal;
	CComboListCtrl	m_autolist;
	CComboListCtrl	m_autolist2;
	CComboListCtrl	m_autolistTotal;
	CComboBox	m_showItem;
	CComboBox	m_levelway;
	CBitButtonNL	m_addItem;
	CBitButtonNL	m_sure;
	CBitButtonNL	m_delItem;
	CBitButtonNL	m_cancel;
	int		m_chip;
	//}}AFX_DATA
	bool shootlevel;
	void SetDialogFace();
	void InsertItem(CString str);
	bool OnInitShowItem();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccumulateLevel)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAccumulateLevel)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnExit();
	afx_msg void OnAddItem();
	afx_msg void OnCancel();
	afx_msg void OnDeleteItem();
	afx_msg void OnIf();
	afx_msg void OnIr();
	afx_msg void OnVf();
	afx_msg void OnVr();
	afx_msg void OnDvf();
	afx_msg void OnThy();
	afx_msg void OnIv();
	afx_msg void OnWl();
	afx_msg void OnPwl();
	afx_msg void OnDeltaWL();
	afx_msg void OnCct();
	afx_msg void OnCri();
	afx_msg void OnPur();
	afx_msg void Onlevelchip1();
	afx_msg void Onlevelchip2();
	afx_msg void Onlevelchip3();
	afx_msg void OnSure();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnShootCal();
	afx_msg void OnXYZCheck();
	afx_msg bool OnfastLevel();
	afx_msg void OnApplylevels();
	afx_msg void OnXyz();
	afx_msg void OnSelchangeShowItem();
	//}}AFX_MSG
	void OnInitList(); 
	bool ShowLevelTool(bool shoot);
	bool SetAutoList2();
	bool updateTotalList();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCUMULATELEVEL_H__E22D5BAC_3D93_47CD_A6CE_2F451D607571__INCLUDED_)
