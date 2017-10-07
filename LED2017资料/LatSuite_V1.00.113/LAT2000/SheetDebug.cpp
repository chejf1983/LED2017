// SheetDebug.cpp : implementation file
//

#include "stdafx.h"
#include "SheetDebug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BOOL g_bEnglish;
/////////////////////////////////////////////////////////////////////////////
// CSheetDebug

IMPLEMENT_DYNAMIC(CSheetDebug, CPropertySheet)

CSheetDebug::CSheetDebug(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CSheetDebug::CSheetDebug(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CSheetDebug::~CSheetDebug()
{
}


BEGIN_MESSAGE_MAP(CSheetDebug, CPropertySheet)
	//{{AFX_MSG_MAP(CSheetDebug)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSheetDebug message handlers

BOOL CSheetDebug::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// Move the OK button
	CWnd* pbtnOk = GetDlgItem(IDOK);
	ASSERT(pbtnOk);

	CRect rectSheet;
	GetWindowRect(rectSheet);

	// get size of ok button
	CRect rectOkBtn;
	pbtnOk->GetWindowRect(rectOkBtn);

	pbtnOk->EnableWindow(FALSE);

	// get border space between btn bottom and sheet bottom 
	int iBorder = rectSheet.bottom - rectOkBtn.bottom;

	// resize sheet
	rectSheet.right ;
	rectSheet.bottom = rectOkBtn.top;
	MoveWindow(rectSheet);
	
/*	// 1 - Load the icon from the application's resources
	HICON hicon = AfxGetApp()->LoadIcon( IDI_DEBUG);
	ASSERT( hicon != NULL );

	// 2 - Associate the icon with the dialog box
	SetIcon( hicon, TRUE );	*/

	return bResult;
}

 

 

 

 

 

 

 
