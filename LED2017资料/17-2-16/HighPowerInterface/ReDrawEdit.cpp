// ReDrawEdit.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "ReDrawEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReDrawEdit

CReDrawEdit::CReDrawEdit()
{
	m_hBrush = CreateSolidBrush(RGB(255, 255, 255));
}

CReDrawEdit::~CReDrawEdit()
{
}


BEGIN_MESSAGE_MAP(CReDrawEdit, CEdit)
	//{{AFX_MSG_MAP(CReDrawEdit)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReDrawEdit message handlers

HBRUSH CReDrawEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CEdit::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	pDC->SetBkMode(TRANSPARENT);
	hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CReDrawEdit::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
//	return CEdit::OnEraseBkgnd(pDC);
	return true;
}
