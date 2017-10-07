#if !defined(AFX_DLGCALPLFLUX_H__62C0B495_AFB8_43AA_A581_53CCB9099A39__INCLUDED_)
#define AFX_DLGCALPLFLUX_H__62C0B495_AFB8_43AA_A581_53CCB9099A39__INCLUDED_

#include "DrawForMySpec.h"
#include "SpectData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCalPLFlux.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCalPLFlux dialog

class CDlgCalPLFlux : public CDialog
{
// Construction
public:
	void ReDraw();
	BOOL AUTO(float &fIntTime);
	int m_iCurSele;
	DATA_DRAW m_drawData;
	CSpectData m_spData;

	CString m_strNameE;
	CString m_strNameC;

	void ReListSele();
	void ReList();
	CDlgCalPLFlux(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCalPLFlux)
	enum { IDD = IDD_CAL_FE };
	CComboBox	m_cSele;
	CButton	m_cCancel;
	CListCtrl	m_cList;
	CEdit	m_cName;
	CEdit	m_cK;
	CEdit	m_cFlux;
	CDrawForMySpec	m_cDraw;
	CButton	m_cSave;
	CButton	m_cDel;
	BOOL	m_bUseFluxPL;
	int		m_iSele;
	float	m_fFlux;
	float	m_fK;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalPLFlux)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalPLFlux)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCalFlux();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonDel();
	virtual void OnCancel();
	afx_msg void OnSelchangeComboSele();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCALPLFLUX_H__62C0B495_AFB8_43AA_A581_53CCB9099A39__INCLUDED_)
