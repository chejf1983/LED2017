// MySheet.cpp : implementation file
//

#include "stdafx.h"
#include "MySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySheet

IMPLEMENT_DYNAMIC(CMySheet, CPropertySheet)

CMySheet::CMySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CMySheet::CMySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CMySheet::~CMySheet()
{
}


BEGIN_MESSAGE_MAP(CMySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CMySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySheet message handlers

BOOL CMySheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
	// Move the OK button

	////////////////////////
	//为了不要那个应用按钮
	////////////////////////

	CWnd* pbtnOk = GetDlgItem(IDOK);
	ASSERT(pbtnOk);
	CWnd* pbtnCancel = GetDlgItem(IDCANCEL);
	ASSERT(pbtnCancel);
	CWnd* pbtnApply = GetDlgItem(ID_APPLY_NOW);
	ASSERT(pbtnApply);

	CRect t1,t2,t3;
	pbtnOk->GetClientRect(&t1);
	pbtnOk->ClientToScreen(&t1);
	ScreenToClient(&t1);

	pbtnCancel->GetClientRect(&t2);
	pbtnCancel->ClientToScreen(&t2);
	ScreenToClient(&t2);

	pbtnApply->GetClientRect(&t3);
	pbtnApply->ClientToScreen(&t3);
	ScreenToClient(&t3);

	pbtnOk->MoveWindow(t2);
	pbtnCancel->MoveWindow(t3);

	pbtnApply->ShowWindow(FALSE);

	return bResult;
}
