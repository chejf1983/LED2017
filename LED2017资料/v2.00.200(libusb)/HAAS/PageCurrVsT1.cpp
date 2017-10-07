// PageCurrVsT1.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "PageCurrVsT1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageCurrVsT1 property page

IMPLEMENT_DYNCREATE(CPageCurrVsT1, CPropertyPage)

CPageCurrVsT1::CPageCurrVsT1() : CPropertyPage(CPageCurrVsT1::IDD)
{
	//{{AFX_DATA_INIT(CPageCurrVsT1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	HICON hIcon = AfxGetApp()->LoadIcon( IDI_CURR_VS_L_1 );
	ASSERT( hIcon != NULL );
	m_psp.hIcon = hIcon;
	m_psp.dwFlags &= ~PSP_USEICONID;
	m_psp.dwFlags |= PSP_USEHICON;

	m_bFir = TRUE;
}

CPageCurrVsT1::~CPageCurrVsT1()
{
}

void CPageCurrVsT1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageCurrVsT1)
	DDX_Control(pDX, IDC_LIST, m_cList);
	DDX_Control(pDX, IDC_DRAW, m_cDraw);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageCurrVsT1, CPropertyPage)
	//{{AFX_MSG_MAP(CPageCurrVsT1)
	ON_WM_SIZE()
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageCurrVsT1 message handlers

BOOL CPageCurrVsT1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bFir = FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageCurrVsT1::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_bFir)
	{
		CRect clRect;
		GetClientRect(clRect);
		
		CRect toRect;
		toRect.top=clRect.top;
		toRect.bottom=clRect.bottom;
		toRect.left=clRect.left;
		toRect.right=clRect.right-70;
		
		m_cDraw.MoveWindow(toRect);	
		
		toRect.bottom=toRect.bottom;
		toRect.left=toRect.right;
		toRect.right=clRect.right;
		m_cList.MoveWindow(toRect);
	}
}

void CPageCurrVsT1::OnSelchangeList() 
{
	// TODO: Add your control notification handler code here
	int iCur=m_cList.GetCurSel();
	if(iCur<0)
		return;
	
	::PostMessage(GetParent()->GetParent()->m_hWnd,WM_LIST_SELE_T,1,iCur);		
}

void CPageCurrVsT1::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CPropertyPage::OnLButtonDown(nFlags, point);
}

void CPageCurrVsT1::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CPropertyPage::OnMouseMove(nFlags, point);
}
