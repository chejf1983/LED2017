#if !defined(AFX_SETUP3_H__2955ABA1_A080_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_SETUP3_H__2955ABA1_A080_11DB_949D_00055D02EEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Setup3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetup3 dialog

class CSetup3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetup3)

// Construction
public:
	CSetup3();
	~CSetup3();

// Dialog Data
	//{{AFX_DATA(CSetup3)
	enum { IDD = IDD_SETUP3 };
	CButton	m_cuseTrig;
	CComboBox	m_cTestListCalSele;
	CEdit	m_cWL2;
	CEdit	m_cWL1;
	CEdit	m_cPulseTime;
	CEdit	m_cPulseNum;
	CStatic	m_cPulseNumS;
	CStatic	m_cPulseTimeS;
	CStatic	m_cSeleLS;
	CComboBox	m_cSeleL;
	CStatic	m_cIS3;
	CEdit	m_cIntK;
	CEdit	m_cDistance;
	CStatic	m_cIS2;
	CStatic	m_cIS1;
	CButton	m_cTrigMode2;
	CStatic	m_cTrig;
	CButton	m_cTrigMode1;
	CComboBox	m_cTestType;
	CStatic	m_cPES;
	CComboBox	m_cPE;
	CComboBox	m_cLamp;
	CButton	m_cAtt;
	CButton	m_cAtt2;
	CStatic	m_cA1;
	CButton	m_cAtt1;
	CStatic	m_cS1;
	CComboBox	m_cMode;
	CComboBox	m_cLED;
	CComboBox	m_cBin;
	int		m_iAutoTime2;
	int		m_iTestType;
	int		m_iBin;
	int		m_iMode;
	int		m_iLED;
	BOOL	m_bAtt;
	int		m_iAtt;
	int		m_iLamp;
	int		m_iPEType;
	BOOL	m_bPhoto;
	int		m_iTrigMode;
	BOOL	m_bTrig;
	float	m_fDistance;
	float	m_fIntK;
	int		m_iSeleL;
	int		m_iPulseNum;
	float	m_fPulseTime;
	float	m_fWL1;
	float	m_fWL2;
	int		m_iTestListCalSele;
	BOOL	m_bUseListCalSele;
	int		m_iSigType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetup3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetup3)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboLed();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnCheckType();
	afx_msg void OnCheckAtt();
	afx_msg void OnRadioAtt1();
	afx_msg void OnRadioAtt2();
	afx_msg void OnSelchangeComboLamp();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnCheckTrig();
	afx_msg void OnSelchangeComboType();
	afx_msg void OnCheckListCal();
	afx_msg void OnSelchangeComboSigType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUP3_H__2955ABA1_A080_11DB_949D_00055D02EEF1__INCLUDED_)
