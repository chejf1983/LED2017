// PageCurrVsL2.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "PageCurrVsL2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageCurrVsL2 property page

IMPLEMENT_DYNCREATE(CPageCurrVsL2, CPropertyPage)

CPageCurrVsL2::CPageCurrVsL2() : CPropertyPage(CPageCurrVsL2::IDD)
{
	//{{AFX_DATA_INIT(CPageCurrVsL2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	HICON hIcon = AfxGetApp()->LoadIcon( IDI_CURR_VS_L_2 );
	ASSERT( hIcon != NULL );
	m_psp.hIcon = hIcon;
	m_psp.dwFlags &= ~PSP_USEICONID;
	m_psp.dwFlags |= PSP_USEHICON;

	m_bFir = TRUE;
}

CPageCurrVsL2::~CPageCurrVsL2()
{
}

void CPageCurrVsL2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageCurrVsL2)
	DDX_Control(pDX, IDC_LIST, m_cList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageCurrVsL2, CPropertyPage)
	//{{AFX_MSG_MAP(CPageCurrVsL2)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageCurrVsL2 message handlers

void CPageCurrVsL2::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_bFir)
	{
		CRect clRect;
		GetClientRect(clRect);
		m_cList.MoveWindow(clRect);	
	}		
}

BOOL CPageCurrVsL2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_cList.SetExtendedStyle(m_cList.GetExtendedStyle()  | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	m_bFir = FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
