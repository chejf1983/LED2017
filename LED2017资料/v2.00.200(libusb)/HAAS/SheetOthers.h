#if !defined(AFX_SHEETOTHERS_H__08B57E63_52A2_11D6_80F1_52544CBE8249__INCLUDED_)
#define AFX_SHEETOTHERS_H__08B57E63_52A2_11D6_80F1_52544CBE8249__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SheetOthers.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSheetOthers

class CSheetOthers : public CPropertySheet
{
	DECLARE_DYNAMIC(CSheetOthers)

// Construction
public:
	CSheetOthers(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSheetOthers(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSheetOthers)
	public:
	virtual BOOL OnInitDialog();
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSheetOthers();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSheetOthers)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEETOTHERS_H__08B57E63_52A2_11D6_80F1_52544CBE8249__INCLUDED_)
