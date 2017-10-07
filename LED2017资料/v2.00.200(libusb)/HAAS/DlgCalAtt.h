#if !defined(AFX_DLGCALATT_H__6E5A77D2_B9C5_4948_A3C6_01F638EE2E9F__INCLUDED_)
#define AFX_DLGCALATT_H__6E5A77D2_B9C5_4948_A3C6_01F638EE2E9F__INCLUDED_

#include "Global_MySpec.h"
#include "DrawForMySpec.h"
#include "SpectData.h"
#include "Label.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCalAtt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCalAtt dialog

class CDlgCalAtt : public CDialog
{
// Construction
public:
	BOOL Test();
	void ReList();
	void ReDraw();
	void EnableShow(BOOL bStart);

	BOOL m_bCancel;
	float m_fIntTime1;
	float m_fIntTime2;
	float m_fRelN[10001];//高的数据
	float m_fRelR[10001];//低的数据

	CSpectData m_spData;
	DATA_DRAW  m_drawData;
	CImageList m_SmallImageList;

	CDlgCalAtt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCalAtt)
	enum { IDD = IDD_CAL_ATT };
	CButton	m_cExit;
	CButton	m_cStop;
	CButton	m_cSave;
	CButton	m_cCal;
	CDrawForMySpec	m_cDraw;
	CLabel	m_cIP;
	CListCtrl	m_cList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalAtt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalAtt)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCal();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonSave();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCALATT_H__6E5A77D2_B9C5_4948_A3C6_01F638EE2E9F__INCLUDED_)
