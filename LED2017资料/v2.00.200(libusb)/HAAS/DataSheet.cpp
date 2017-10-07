// DataSheet.cpp : implementation file
//

#include "stdafx.h"
#include "Myspec.h"
#include "DataSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataSheet

IMPLEMENT_DYNAMIC(CDataSheet, CPropertySheet)


CDataSheet::CDataSheet(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_DATA_SHEET_CAPTION, pParentWnd, iSelectPage)
{
	AddPage(&m_pageData1);
	AddPage(&m_pageData2);
	AddPage(&m_pageData4);
//	AddPage(&m_pageData4);
}


CDataSheet::~CDataSheet()
{
}


BEGIN_MESSAGE_MAP(CDataSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CDataSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataSheet message handlers

BOOL CDataSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
	
	return bResult;
}
