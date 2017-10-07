// SheetOthers.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "SheetOthers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSheetOthers

IMPLEMENT_DYNAMIC(CSheetOthers, CPropertySheet)

CSheetOthers::CSheetOthers(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CSheetOthers::CSheetOthers(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CSheetOthers::~CSheetOthers()
{
}


BEGIN_MESSAGE_MAP(CSheetOthers, CPropertySheet)
	//{{AFX_MSG_MAP(CSheetOthers)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSheetOthers message handlers

BOOL CSheetOthers::OnInitDialog() 
{

	BOOL bResult = CPropertySheet::OnInitDialog();

//	ModifyStyle(0,WS_MINIMIZEBOX|WS_POPUP);
	
	// Move the OK button
	CWnd* pbtnOk = GetDlgItem(IDOK);
	ASSERT(pbtnOk);

	CRect rectSheet;
	GetWindowRect(rectSheet);

	// get size of ok button
	CRect rectOkBtn;
	pbtnOk->GetWindowRect(rectOkBtn);

	// get border space between btn bottom and sheet bottom 
	int iBorder = rectSheet.bottom - rectOkBtn.bottom;

	// resize sheet
	rectSheet.right ;
	rectSheet.bottom = rectOkBtn.top;
	MoveWindow(rectSheet);
	
/*	// 1 - Load the icon from the application's resources
	HICON hicon = AfxGetApp()->LoadIcon( IDI_SPECT);
	ASSERT( hicon != NULL );

	// 2 - Associate the icon with the dialog box
	SetIcon( hicon, TRUE );	*/

	return bResult;
}

 
