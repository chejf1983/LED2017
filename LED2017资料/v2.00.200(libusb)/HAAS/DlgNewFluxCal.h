#if !defined(AFX_DLGNEWFLUXCAL_H__B4D1621C_0D9F_47E4_814F_89F2BC009C7E__INCLUDED_)
#define AFX_DLGNEWFLUXCAL_H__B4D1621C_0D9F_47E4_814F_89F2BC009C7E__INCLUDED_

#include "SpectData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNewFluxCal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNewFluxCal dialog

class CDlgNewFluxCal : public CDialog
{
// Construction
public:
	BOOL Test();
	CDlgNewFluxCal(CWnd* pParent = NULL);   // standard constructor

	CSpectData m_spData;

// Dialog Data
	//{{AFX_DATA(CDlgNewFluxCal)
	enum { IDD = IDD_NEW_FLUX_CAL };
	CButton	m_cExit;
	CButton	m_cSaveCal;
	CButton	m_cCal;
	CEdit	m_cTestFlux;
	float	m_fStaFlux;
	CString	m_strRemarks;
	CString	m_strDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNewFluxCal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNewFluxCal)
	virtual void OnOK();
	afx_msg void OnButtonCal();
	afx_msg void OnButtonSaveCal();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNEWFLUXCAL_H__B4D1621C_0D9F_47E4_814F_89F2BC009C7E__INCLUDED_)
