#if !defined(AFX_DATASHEETT_H__4B43B7C1_FDD9_11D9_ABAD_00055D02EEF2__INCLUDED_)
#define AFX_DATASHEETT_H__4B43B7C1_FDD9_11D9_ABAD_00055D02EEF2__INCLUDED_

#include "PageCurrVsT1.h"
#include "PageCurrVsT2.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataSheetT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataSheetT

class CDataSheetT : public CPropertySheet
{
	DECLARE_DYNAMIC(CDataSheetT)

// Construction
public:
	CDataSheetT(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CPageCurrVsT1 m_dPageT1;
	CPageCurrVsT2 m_dPageT2;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataSheetT)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDataSheetT();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDataSheetT)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATASHEETT_H__4B43B7C1_FDD9_11D9_ABAD_00055D02EEF2__INCLUDED_)
