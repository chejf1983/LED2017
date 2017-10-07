#if !defined(AFX_DLGSPECTRUMCAL_H__1435D5A1_9811_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_DLGSPECTRUMCAL_H__1435D5A1_9811_11DB_949D_00055D02EEF1__INCLUDED_

#include "DrawForMySpec.h"
#include "SpectData.h"
#include "Label.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSpectrumCal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSpectrumCal dialog

class CDlgSpectrumCal : public CDialog
{
// Construction
public:
	//光源处理
	CArray<CString,CString> m_strListCtrlFile;

	CString Pro(CString sStr);
	BOOL GetLampName();

	void SetShowIcon(BOOL bNotTest);
	BOOL AllModeTest();
	void Show();

	float m_fTempSP1;
	float m_fTempSP2;
	int   m_iTempBin;
	int   m_iTempMode;

	int m_iCurMode;

	int m_iNum;
	int m_iCur;
	BOOL Test();
	BOOL m_bCancel;
	void EnableShow(BOOL bStart);
	void ReList();
	void SaveSet();
	DATA_DRAW m_drawData;
	CSpectData m_spData[20];

	CImageList m_SmallImageList;

	void ReDraw();
	CDlgSpectrumCal(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSpectrumCal)
	enum { IDD = IDD_SPECTRUM_CAL };
	CStatic	m_cListS;
	CComboBox	m_cListCalSele;
	CProgressCtrl	m_cPro;
	CButton	m_cAuto;
	CComboBox	m_cLamp;
	CComboBox	m_cLampType;
	CButton	m_cAll;
	CEdit	m_cAveN;
	CStatic	m_cIS1;
	CEdit	m_cDistance;
	CButton	m_cWY;
	CLabel	m_cSet;
	CButton	m_cStop;
	CListCtrl	m_cList;
	CEdit	m_cStaVol;
	CStatic	m_cStaPhS;
	CButton	m_cExit;
	CButton	m_cSave;
	CButton	m_cON;
	CButton	m_cOFF;
	CButton	m_cCal;
	CLabel	m_cIP;
	CEdit	m_cStaTc;
	CEdit	m_cStaPh;
	CEdit	m_cStaCurr;
	CEdit	m_cIntTime;
	CComboBox	m_cCalPhType;
	CDrawForMySpec	m_cDraw;
	float	m_fIntTime;
	float	m_fStaCurr;
	float	m_fStaTc;
	float	m_fStaPh;
	int		m_iCalPhType;
	float	m_fStaVol;
	BOOL	m_bWY;
	float	m_fDistance;
	int		m_iAveN;
	BOOL	m_bAll;
	int		m_iLampType;
	int		m_iLamp;
	BOOL	m_bAuto;
	int		m_iListCalSele;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSpectrumCal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSpectrumCal)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSelchangeComboType();
	afx_msg void OnButtonCal();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonOn();
	afx_msg void OnButtonOff();
	afx_msg void OnButtonStop();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckWy();
	afx_msg void OnStaticSetup();
	afx_msg void OnCheckAll();
	afx_msg void OnSelchangeComboLamp();
	afx_msg void OnSelchangeComboLampType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSPECTRUMCAL_H__1435D5A1_9811_11DB_949D_00055D02EEF1__INCLUDED_)
