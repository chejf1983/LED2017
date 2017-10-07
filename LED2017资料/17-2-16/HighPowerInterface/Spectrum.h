#if !defined(AFX_SPECTRUM_H__2D5F23CF_E2D6_4C53_9E01_889642F1CF32__INCLUDED_)
#define AFX_SPECTRUM_H__2D5F23CF_E2D6_4C53_9E01_889642F1CF32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Spectrum.h : header file
//
#include "resFile\ResizingDialog\ResizingDialog.h"
/////////////////////////////////////////////////////////////////////////////
// CSpectrum dialog

class CSpectrum : public CResizingDialog
{
// Construction
public:
	CSpectrum(CWnd* pParent = NULL);   // standard constructor
	BOOL MoveWindowSmall();
	BOOL MoveWindowBig();
	int width;
	CWnd *pWnd_picture; 
	CDC *pDC_picture;
	RECT rect; 
// Dialog Data
	//{{AFX_DATA(CSpectrum)
	enum { IDD = IDD_Spectrum };
	//}}AFX_DATA
	void setdrawY(int chip);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpectrum)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpectrum)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSpectrumPicture();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECTRUM_H__2D5F23CF_E2D6_4C53_9E01_889642F1CF32__INCLUDED_)
