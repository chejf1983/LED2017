#if !defined(AFX_DLGCHECKBW_H__2981A961_A09B_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_DLGCHECKBW_H__2981A961_A09B_11DB_949D_00055D02EEF1__INCLUDED_

#include "DrawForMySpec.h"
#include "SpectData.h"
#include "Label.h"
#include "WLCorData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCheckBW.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCheckBW dialog

class CDlgCheckBW : public CDialog
{
	// Construction
public:
	int m_iSele;

	BOOL GetBW();
	int m_iPerTime;
	
	BOOL WLSET_Save();
	BOOL WLSET_Load();
	BOOL Test();
	
	void ShowErr();
	void ShowEnable(BOOL bStart);
	
	void ReListWL();
	void ReDraw();
	
	int  m_iTestType;
	BOOL m_bCancel;
	int  m_iHaveErr;
	float m_fErr[4];
	
	CWLCorData  m_wlCorData;
	DATA_DRAW m_drawData;
	CSpectData m_spData;
	
	CDlgCheckBW(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CDlgCheckBW)
	enum { IDD = IDD_CHECK_BW };
	CButton	m_cOk;
	CButton	m_cRR;
	CButton	m_cR;
	CButton	m_cLL;
	CButton	m_cL;
	CLabel	m_cEV;
	CEdit	m_cAvgN;
	CEdit	m_cIntTime;
	CButton	m_cExit;
	CListCtrl	m_cListWL;
	CLabel	m_cIP;
	CDrawForMySpec	m_cDraw;
	CButton	m_cAuto;
	CButton	m_cTest;
	CButton	m_cStop;
	CButton	m_cStart;
	BOOL	m_bAuto;
	int		m_iAvgN;
	float	m_fIntTime;
	BOOL	m_bShowCur;
	float	m_fStaWL;
	float	m_fSetWL1;
	float	m_fSetWL2;
	BOOL	m_bZoom;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCheckBW)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlgCheckBW)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonTest();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	virtual void OnCancel();
	afx_msg void OnCheckAuto();
	afx_msg void OnButtonLl();
	afx_msg void OnButtonL();
	afx_msg void OnButtonR();
	afx_msg void OnButtonRr();
	afx_msg void OnCheckCur();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCustomdrawMyList ( NMHDR* pNMHDR, LRESULT* pResult );
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonGetHf();
	afx_msg void OnCheckZoom();
	afx_msg void OnChangeEditX1();
	afx_msg void OnChangeEditX2();
	afx_msg void OnButtonOk();
	afx_msg void OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHECKBW_H__2981A961_A09B_11DB_949D_00055D02EEF1__INCLUDED_)
