#if !defined(AFX_DLGFLUXCAL_H__E4EC3C60_135C_4E2D_A4B1_CC8BF1BAFF8C__INCLUDED_)
#define AFX_DLGFLUXCAL_H__E4EC3C60_135C_4E2D_A4B1_CC8BF1BAFF8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFluxCal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFluxCal dialog

class CDlgFluxCal : public CDialog
{
// Construction
public:
	BOOL bGo;
	CFont Font1;

	float m_fTempFluxK;
	float m_fFluxK;

	BOOL FluxCheck();

	CDlgFluxCal(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFluxCal)
	enum { IDD = IDD_FLUX_CAL };
	CButton	m_cTestSelfK;
	CStatic	m_cModeS2;
	CEdit	m_cModeSelfK;
	CStatic	m_cModeS;
	CEdit	m_cModeK;
	CButton	m_cCal;
	CButton	m_cCheck;
	CButton	m_cSave;
	CEdit	m_cFlux;
	CEdit	m_cStaFlux;
	CStatic	m_cS6;
	CStatic	m_cS5;
	CStatic	m_cS4;
	CStatic	m_cS3;
	CStatic	m_cS2;
	CStatic	m_cS1;
	float	m_fStaFlux;
	float	m_fModeFluxK;
	float	m_fModeSelfK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFluxCal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFluxCal)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCal();
	afx_msg void OnButtonCheck();
	afx_msg void OnButtonSave();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonZero();
	afx_msg void OnButtonWy();
	afx_msg void OnTestSelfK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFLUXCAL_H__E4EC3C60_135C_4E2D_A4B1_CC8BF1BAFF8C__INCLUDED_)
