#if !defined(AFX_DEBUG1_H__070BA781_93F0_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_DEBUG1_H__070BA781_93F0_11DB_949D_00055D02EEF1__INCLUDED_

#include "DrawForMySpec.h"
#include "Label.h"
#include "SpectData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Debug1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDebug1 dialog

class CDebug1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDebug1)

// Construction
public:
	void EnableShowNew(BOOL bStart);
	void GetPX();
	BOOL GetZSG();
	BOOL GetBW();

	CSpectData m_spData;
	void OVER();
	void EnableShow(BOOL bStart);
	BOOL Test(float fIntTime, int iAvgN,float fData[], int &iN);
	float m_fAD[10000];
	int   m_iN;

	CString m_strPathName;
	BOOL m_bCancel;
	DEBUG_DRAW m_debugDrawPara;

	void ReDraw();
	CDebug1();
	~CDebug1();

// Dialog Data
	//{{AFX_DATA(CDebug1)
	enum { IDD = IDD_DEBUG1 };
	CButton	m_cStart2;
	CButton	m_cStop2;
	CStatic	m_cBW;
	CStatic	m_cWLHF;
	CLabel	m_cLevel;
	CStatic	m_cHalf;
	CLabel	m_cSet;
	CEdit	m_cX2;
	CEdit	m_cX1;
	CStatic	m_cX12;
	CButton	m_cOK;
	CEdit	m_cWL;
	CEdit	m_cPix;
	CEdit	m_cAD;
	CEdit	m_cIntTime;
	CEdit	m_cAvgN;
	CButton	m_cTest;
	CButton	m_cStop;
	CButton	m_cStart;
	CButton	m_cExit;
	CDrawForMySpec	m_cDraw;
	int		m_iAvgN;
	float	m_fIntTime;
	BOOL	m_bLine;
	int		m_iPix;
	float	m_fWL;
	BOOL	m_bSetZoom;
	int		m_iX1;
	int		m_iX2;
	BOOL	m_bCro;
	int		m_iJType;
	BOOL	m_bHalfWL;
	int		m_iLevel_ZS;
	float	m_fWLPX;
	BOOL	m_bNotUseColor;
	int		m_iPer;
	int		m_iPer2;
	int		m_iPerType;
	int		m_iPixSele;
	float	m_fIntTime1;
	float	m_fIntTime2;
	float	m_fIntervalTime;
	int		m_iPixSele2;
	int		m_iStepType;
	BOOL	m_bMoveDark;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDebug1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDebug1)
	afx_msg void OnButtonTest();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonExit();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckLine();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonOk();
	afx_msg void OnCheckZoom();
	afx_msg void OnChangeEditX1();
	afx_msg void OnChangeEditX2();
	afx_msg void OnButtonSave();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonZero();
	afx_msg void OnStaticSetup();
	afx_msg void OnButtonZeroC();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnButtonTestJ();
	afx_msg void OnButton2();
	afx_msg void OnCheckHalfWl();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnButtonOk2();
	afx_msg void OnButtonStart2();
	afx_msg void OnButtonStop2();
	afx_msg void OnButtonInit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	static UINT Thread(LPVOID pPar);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEBUG1_H__070BA781_93F0_11DB_949D_00055D02EEF1__INCLUDED_)
