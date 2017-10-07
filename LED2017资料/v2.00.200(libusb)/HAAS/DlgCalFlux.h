#if !defined(AFX_DLGCALFLUX_H__F074DD5D_888B_49C2_85F0_15F3BB8B4BC0__INCLUDED_)
#define AFX_DLGCALFLUX_H__F074DD5D_888B_49C2_85F0_15F3BB8B4BC0__INCLUDED_

#include "DrawForMySpec.h"
#include "SpectData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCalFlux.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCalFlux dialog

class CDlgCalFlux : public CDialog
{
// Construction
public:
	BOOL bGo;
	BOOL FluxCheck();
	BOOL AUTO(float &fIntTime);

	int m_iCurSele;
	void ReListSele();
	void ReList();
	DATA_DRAW m_drawData;
	CSpectData m_spData;

	CDlgCalFlux(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCalFlux)
	enum { IDD = IDD_CAL_FLUX };
	CButton	m_cTestSelf;
	CStatic	m_cModeS2;
	CEdit	m_cModeSelfK;
	CEdit	m_cModeK;
	CStatic	m_cModeS;
	CEdit	m_cFluxCheck;
	CButton	m_cCheck;
	CEdit	m_cName;
	CEdit	m_cCurr;
	CEdit	m_cFlux;
	CStatic	m_cSeleS;
	CListCtrl	m_cList;
	CEdit	m_cK;
	CComboBox	m_cSele;
	CButton	m_cSave;
	BOOL	m_bUseCalFlux;
	int		m_iSele;
	float	m_fCurr;
	float	m_fFlux;
	CString	m_strName;
	float	m_fK;
	float	m_fModeFluxK;
	float	m_fModeSelfK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalFlux)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalFlux)
	afx_msg void OnCheckUsbCalFlux();
	afx_msg void OnSelchangeComboSele();
	afx_msg void OnButtonOn();
	afx_msg void OnButtonOff();
	afx_msg void OnButtonCal();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonDel();
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditK();
	afx_msg void OnButtonCheck();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTestSelfK();
	afx_msg void OnChangeEditModeK();
	afx_msg void OnChangeEditModeK2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCALFLUX_H__F074DD5D_888B_49C2_85F0_15F3BB8B4BC0__INCLUDED_)
