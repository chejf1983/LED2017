#if !defined(AFX_DLGSPECTRUMCALU_H__50F143A1_64C0_4828_B6BA_893B6500741E__INCLUDED_)
#define AFX_DLGSPECTRUMCALU_H__50F143A1_64C0_4828_B6BA_893B6500741E__INCLUDED_

#include "DrawForMySpec.h"
#include "SpectData.h"
#include "Label.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSpectrumCalU.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSpectrumCalU dialog

class CDlgSpectrumCalU : public CDialog
{
// Construction
public:
	void SetShowIcon(BOOL bNotTest);
	BOOL AllModeTest();

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
	CDlgSpectrumCalU(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSpectrumCalU)
	enum { IDD = IDD_SPECTRUM_CAL_U };
	CEdit	m_cAveN;
	CButton	m_cAll;
	BOOL	m_bAll;
	CLabel	m_cSet;
	CButton	m_cStop;
	CListCtrl	m_cList;
	CButton	m_cExit;
	CButton	m_cSave;
	CButton	m_cOFF;
	CButton	m_cCal;
	CLabel	m_cIP;
	CEdit	m_cIntTime;
	CDrawForMySpec	m_cDraw;
	float	m_fIntTime;
	int		m_iAveN;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSpectrumCalU)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSpectrumCalU)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnButtonCal();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonOff();
	afx_msg void OnButtonStop();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckWy();
	afx_msg void OnStaticSetup();
	afx_msg void OnCheckAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSPECTRUMCALU_H__50F143A1_64C0_4828_B6BA_893B6500741E__INCLUDED_)
