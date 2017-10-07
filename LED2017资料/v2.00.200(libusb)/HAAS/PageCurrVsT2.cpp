// PageCurrVsT2.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "PageCurrVsT2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageCurrVsT2 property page

IMPLEMENT_DYNCREATE(CPageCurrVsT2, CPropertyPage)

CPageCurrVsT2::CPageCurrVsT2() : CPropertyPage(CPageCurrVsT2::IDD)
{
	//{{AFX_DATA_INIT(CPageCurrVsT2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	HICON hIcon = AfxGetApp()->LoadIcon( IDI_CURR_VS_L_2 );
	ASSERT( hIcon != NULL );
	m_psp.hIcon = hIcon;
	m_psp.dwFlags &= ~PSP_USEICONID;
	m_psp.dwFlags |= PSP_USEHICON;

	m_bFir = TRUE;
}

CPageCurrVsT2::~CPageCurrVsT2()
{
}

void CPageCurrVsT2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageCurrVsT2)
	DDX_Control(pDX, IDC_LIST, m_cList);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageCurrVsT2, CPropertyPage)
	//{{AFX_MSG_MAP(CPageCurrVsT2)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageCurrVsT2 message handlers

BOOL CPageCurrVsT2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cList.SetExtendedStyle(m_cList.GetExtendedStyle()  | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	m_bFir = FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageCurrVsT2::OnSize(UINT nType, int cx, int cy) 
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
