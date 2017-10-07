#if !defined(AFX_SETPARAMETER_H__98F49110_E978_48C8_A94E_C7936AAE18F1__INCLUDED_)
#define AFX_SETPARAMETER_H__98F49110_E978_48C8_A94E_C7936AAE18F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetParameter.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "RedrawTabCtrl2.h"
#include "Chip1Dlg.h"
#include "Chip2Dlg.h"
#include "Chip3Dlg.h"
/////////////////////////////////////////////////////////////////////////////
// CSetParameter dialog
UINT UpdateRect(LPVOID lpParam);
class CSetParameter : public CResizingDialog
{
// Construction
public:
	CSetParameter(CWnd* pParent = NULL);   // standard constructor
	CChip1Dlg m_chip1dlg;
	CChip2Dlg m_chip2dlg;
	CChip3Dlg m_chip3dlg;
	int m_CurSelTab;
	CDialog* pDialog[3];

	CWnd *pWnd_picture; 
	CDC *pDC_picture;
	RECT rect;

// Dialog Data
	//{{AFX_DATA(CSetParameter)
	enum { IDD = IDD_SetParameter };
	CButton	m_VFaverage;
	CButton	m_deadLed;
	CButton	m_mixlight;
	CButton	m_setorderhyhand;
	CButton	m_testway;
	CComboBox	m_cbWLSteptypeset;
	CComboBox	m_cbLighttype;
	CComboBox	m_cbWLSteptype;
	CComboBox	m_cbIVtype;
	CRedrawTabCtrl2	m_tabChip;
	//}}AFX_DATA
	bool initdlg();
	void getParameter(); 
	bool ChipsAuthoritydlg();
	void setdrawY();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetParameter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetParameter)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTABChip(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMixLight();
	afx_msg void OnPaint();
	afx_msg void OnDeadLed();
	afx_msg void OnVFaverage();
	afx_msg void OnSetOrderbyhand();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETPARAMETER_H__98F49110_E978_48C8_A94E_C7936AAE18F1__INCLUDED_)
