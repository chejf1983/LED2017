#if !defined(AFX_SHEETDEBUG_H__61310B03_02E5_11D8_A0D4_00055D02EEF1__INCLUDED_)
#define AFX_SHEETDEBUG_H__61310B03_02E5_11D8_A0D4_00055D02EEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SheetDebug.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSheetDebug

class CSheetDebug : public CPropertySheet
{
	DECLARE_DYNAMIC(CSheetDebug)

// Construction
public:
	CSheetDebug(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSheetDebug(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSheetDebug)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSheetDebug();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSheetDebug)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEETDEBUG_H__61310B03_02E5_11D8_A0D4_00055D02EEF1__INCLUDED_)
