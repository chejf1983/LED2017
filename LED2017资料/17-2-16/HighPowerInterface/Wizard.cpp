// Wizard.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "Wizard.h"
#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizard

IMPLEMENT_DYNAMIC(CWizard, CPropertySheet)

CWizard::CWizard(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CWizard::CWizard(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CWizard::~CWizard()
{
}


BEGIN_MESSAGE_MAP(CWizard, CPropertySheet)
	//{{AFX_MSG_MAP(CWizard)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizard message handlers
BOOL CWizard::OnInitDialog() 
{
	CPropertySheet::OnInitDialog();
	
	// TODO: Add extra initialization here
	MoveWindow(200, 200, 490, 435);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CWizard::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
/*	int nCode = HIWORD(wParam);
	if(0 == nCode)
	{
		return true;
	}*/
	return CPropertySheet::OnCommand(wParam, lParam);
}

BOOL CWizard::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBitmap bmp;
	CBitmap *ptrBmpOld;
	BITMAP bm;

	bmp.LoadBitmap(IDB_Wizard);
	bmp.GetBitmap(&bm);

	CRect rect;
	GetClientRect(rect);

	int w,h;
	w=rect.Width()/bm.bmWidth+1;
	h=rect.Height()/bm.bmHeight+1;

	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	ptrBmpOld=dcMemory.SelectObject(&bmp);
	for(int i=0;i<w;i++)
	{
		for(int j=0;j<h;j++)
		{
			pDC->BitBlt
				(
				i*bm.bmWidth,
				j*bm.bmHeight,
				bm.bmWidth,
				bm.bmHeight,
				&dcMemory,
				0,
				0,
				SRCCOPY
				);
		}
	}
	return true;
//	return CPropertySheet::OnEraseBkgnd(pDC);
}


