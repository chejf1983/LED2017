#if !defined(AFX_DEBUG2_H__C9D038E1_94CB_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_DEBUG2_H__C9D038E1_94CB_11DB_949D_00055D02EEF1__INCLUDED_

#include "DrawForMySpec.h"
#include "WLCorData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Debug2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDebug2 dialog

class CDebug2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDebug2)

// Construction
public:
	double m_fC[10];
	int m_iCN;
	CWLCorData  m_wlCorData;
	void ReList();
	BOOL Test(float fIntTime, int iAvgN, float fData[], int &iN);
	void ReDraw();
	float m_fAD[10000];
	int   m_iN;

	CString m_strPathName;
	DEBUG_DRAW m_debugDrawPara;

	CDebug2();
	~CDebug2();

// Dialog Data
	//{{AFX_DATA(CDebug2)
	enum { IDD = IDD_DEBUG2 };
	CButton	m_cSaveCor;
	CComboBox	m_cStaWL;
	CDrawForMySpec	m_cDraw2;
	CListCtrl	m_cWL;
	CEdit	m_cPix;
	CEdit	m_cCor;
	CDrawForMySpec	m_cDraw;
	int		m_iAvgN;
	float	m_fIntTime;
	float	m_fPix;
	int		m_iSeleStaWL;
	int		m_iType;
	float	m_fHalf;
	float	m_fSetDoLimitAD;
	float	m_fSetDoWL;
	int		m_iSR2AngleType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDebug2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDebug2)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonTest();
	afx_msg void OnButtonAdd();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonPeak();
	afx_msg void OnButtonCalc();
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonDel2();
	afx_msg void OnButtonSaveCor();
	afx_msg void OnRadioType2();
	afx_msg void OnRadioType1();
	afx_msg void OnButton1();
	afx_msg void OnChangeEditHalf();
	afx_msg void OnButtonSave2();
	afx_msg void OnButtonOkSet();
	afx_msg void OnSelchangeComboSr2Angle();
	afx_msg void OnButtonLoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEBUG2_H__C9D038E1_94CB_11DB_949D_00055D02EEF1__INCLUDED_)
