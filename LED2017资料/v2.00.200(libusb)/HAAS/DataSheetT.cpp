// DataSheetT.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DataSheetT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataSheetT

IMPLEMENT_DYNAMIC(CDataSheetT, CPropertySheet)

CDataSheetT::CDataSheetT(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_TYPE_SHEET_CAPTION, pParentWnd, iSelectPage)
{
	AddPage(&m_dPageT1);
	AddPage(&m_dPageT2);
}


CDataSheetT::~CDataSheetT()
{
}


BEGIN_MESSAGE_MAP(CDataSheetT, CPropertySheet)
	//{{AFX_MSG_MAP(CDataSheetT)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataSheetT message handlers
