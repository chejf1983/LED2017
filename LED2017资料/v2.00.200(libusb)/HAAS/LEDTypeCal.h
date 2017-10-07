#if !defined(AFX_LEDTYPECAL_H__AF36DA28_5DAF_41EF_A36C_E89A5FB2AD20__INCLUDED_)
#define AFX_LEDTYPECAL_H__AF36DA28_5DAF_41EF_A36C_E89A5FB2AD20__INCLUDED_

#include "DrawForMySpec.h"
#include "SpectData.h"
#include "Label.h"
#include "SpectData.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LEDTypeCal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLEDTypeCal dialog

class CLEDTypeCal : public CDialog
{
// Construction
public:
	CSpectData m_spData;

	CString m_strPathName;

	void EnableShow(BOOL bStart);
	BOOL Test();
	int  m_iCur;
	BOOL m_bCancel;

	CString m_strName_CN;
	CString m_strName_EN;

	float m_fRefS[10001];//
	float m_fRefQ[10001];//

	void ReDraw();
	DATA_DRAW m_drawData;
	void ReList();
	CImageList m_SmallImageList;
	CLEDTypeCal(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLEDTypeCal)
	enum { IDD = IDD_LED_TYPE_CAL };
	CButton	m_cOpen;
	CButton	m_cSave;
	CButton	m_cDel;
	CButton	m_cCancel;
	CLabel	m_cIP;
	CButton	m_cAdd;
	CButton	m_cCal;
	CButton	m_cStop;
	CDrawForMySpec	m_cDraw;
	CListCtrl	m_cList;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLEDTypeCal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLEDTypeCal)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCal();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonAdd();
	virtual void OnCancel();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonSave();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSele();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEDTYPECAL_H__AF36DA28_5DAF_41EF_A36C_E89A5FB2AD20__INCLUDED_)
