#if !defined(AFX_CHIP3DLG_H__0A4DB6BA_C9D9_429C_9DAE_59FB00469283__INCLUDED_)
#define AFX_CHIP3DLG_H__0A4DB6BA_C9D9_429C_9DAE_59FB00469283__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Chip3Dlg.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\ReDrawListCtrl\ComboListCtrl.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
#include "ShootDiagram.h"
/////////////////////////////////////////////////////////////////////////////
// CChip3Dlg dialog

class CChip3Dlg : public CResizingDialog
{
// Construction
public:
	CChip3Dlg(CWnd* pParent = NULL);   // standard constructor
	int chip;
// Dialog Data
	//{{AFX_DATA(CChip3Dlg)
	enum { IDD = IDD_Chip3Dlg };
	CButton	m_tVZ;
	CButton	m_tLV;
	CButton	m_tLE;
	CButton	m_tIE;
	CComboListCtrl	m_calItemList;
	CBitButtonNL	m_clearDark;
	CBitButtonNL	m_getGain;
	CBitButtonNL	m_addDark;
	CBitButtonNL	m_clearCal;
	CBitButtonNL	m_getCal;
	CBitButtonNL	m_caltest;
	CBitButtonNL	m_autosetTime;
	CButton	m_shootset3;
	CComboListCtrl	m_xylist;
	CComboBox	m_cbOpticGain3;
	CComboBox	m_cbWLSteptype3;
	CButton	m_tXYZ;
	CButton	m_tWL;
	CButton	m_tVR;
	CButton	m_tVF;
	CButton	m_tTHY;
	CButton	m_tPWL;
	CButton	m_tPUR;
	CButton	m_tIV;
	CButton	m_tIR;
	CButton	m_tIF;
	CButton	m_tDVF;
	CButton	m_tDeltaWL;
	CButton	m_tCRI;
	CButton	m_tCCT;
	CComboListCtrl	m_chipList;
	//}}AFX_DATA
	bool setParameter(int i);
	bool initdlg();
	void initAuthorityItem();
	void hideAuthorityItem();
	int searchItem(CString str);
	void HandleCheck(CString str, CButton *m_check);
	LRESULT PopulateComboList(WPARAM wParam, LPARAM lParam);
	void SetMixLightParam(bool enable);
	void SetVFaverage(bool enable);
	bool getParameter();
	bool getParameterbyhand();
	bool updateItemforlevel();
	void SetDialogFace();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChip3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChip3Dlg)
	virtual BOOL OnInitDialog();
/*	afx_msg void OnTestIF();
	afx_msg void OnTestIR();
	afx_msg void OnTestVF();
	afx_msg void OnTestVR();
	afx_msg void OnTestDVF();
	afx_msg void OnTestTHY();
	afx_msg void OnTestIV();
	afx_msg void OnTestXYZ();
	afx_msg void OnTestWL();
	afx_msg void OnTestPWL();
	afx_msg void OnTestDeltaWL();
	afx_msg void OnTestPUR();
	afx_msg void OnTestCCT();
	afx_msg void OnTestCRI();*/
	afx_msg void Onshootset3();
	afx_msg void OnClearDark3();
	afx_msg void OnAddDark3();
	afx_msg void OnCalibrationTest3();
	afx_msg void OnAutoSetInteTime3();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClearCalibration();
	afx_msg void OnGetCalibration();
	afx_msg void OnAutoGetOpticGain3();
	afx_msg void OnChangeKlv();
	afx_msg void OnChangeKli();
	afx_msg void OnAddItem();
	afx_msg void OndelItem();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHIP3DLG_H__0A4DB6BA_C9D9_429C_9DAE_59FB00469283__INCLUDED_)
