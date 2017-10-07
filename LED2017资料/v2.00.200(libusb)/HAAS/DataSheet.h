#if !defined(AFX_DATASHEET_H__DFB1CF83_13ED_11DA_ABAD_00055D02EEF1__INCLUDED_)
#define AFX_DATASHEET_H__DFB1CF83_13ED_11DA_ABAD_00055D02EEF1__INCLUDED_

#include "DataPage1.h"
#include "DataPage2.h"
//#include "DataPage3.h"
#include "DataPage4.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataSheet

class CDataSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CDataSheet)

// Construction
public:
	CDataSheet(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	CDataPage1  m_pageData1;
	CDataPage2  m_pageData2;
//	CDataPage3  m_pageData3;
	CDataPage4  m_pageData4;
	virtual ~CDataSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDataSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATASHEET_H__DFB1CF83_13ED_11DA_ABAD_00055D02EEF1__INCLUDED_)
