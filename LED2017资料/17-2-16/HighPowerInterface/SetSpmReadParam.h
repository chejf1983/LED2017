#if !defined(AFX_SETSPMREADPARAM_H__E02D1AD6_225F_40BC_B237_E0D7AC320679__INCLUDED_)
#define AFX_SETSPMREADPARAM_H__E02D1AD6_225F_40BC_B237_E0D7AC320679__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSpmReadParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetSpmReadParam dialog
UINT getSpectrum(LPVOID lpParam);

class CSetSpmReadParam : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetSpmReadParam)

// Construction
public:
	CSetSpmReadParam();
	~CSetSpmReadParam();

	CWnd *pWnd_picture; 
	CDC *pDC_picture;
	RECT Spm_rect; 
// Dialog Data
	//{{AFX_DATA(CSetSpmReadParam)
	enum { IDD = IDD_SetSpmReadParam };
	CButton	m_autoset;
	//}}AFX_DATA
	double Spm_getMaxpower(double time);
	double getTime(double max, double min);
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetSpmReadParam)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnQueryCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetSpmReadParam)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnShowSpectrum();
	afx_msg bool OnAutoSetTime();
	afx_msg void OnSmaller();
	afx_msg void OnEnlarge();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETSPMREADPARAM_H__E02D1AD6_225F_40BC_B237_E0D7AC320679__INCLUDED_)
