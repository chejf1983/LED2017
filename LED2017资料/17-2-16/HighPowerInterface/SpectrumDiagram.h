#if !defined(AFX_SPECTRUMDIAGRAM_H__B32E00BC_1EC4_41FE_86D5_5C080B5F06DA__INCLUDED_)
#define AFX_SPECTRUMDIAGRAM_H__B32E00BC_1EC4_41FE_86D5_5C080B5F06DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpectrumDiagram.h : header file
//
#include "ResizingDialog.h"
/////////////////////////////////////////////////////////////////////////////
// SpectrumDiagram dialog

class SpectrumDiagram : public CResizingDialog
{
// Construction
public:
	SpectrumDiagram(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SpectrumDiagram)
	enum { IDD = IDD_SpectrumDiagram };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SpectrumDiagram)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SpectrumDiagram)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECTRUMDIAGRAM_H__B32E00BC_1EC4_41FE_86D5_5C080B5F06DA__INCLUDED_)
