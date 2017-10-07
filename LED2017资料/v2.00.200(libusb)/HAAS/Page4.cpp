// Page4.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Page4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage4 dialog

IMPLEMENT_DYNCREATE(CPage4, CDialog);

CPage4::CPage4(CWnd* pParent /*=NULL*/)
	: CDialog(CPage4::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPage4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bFir		= TRUE;
	m_pSpData	= NULL;
}


void CPage4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage4)
	DDX_Control(pDX, IDC_CIE1976, m_cCIE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage4, CDialog)
	//{{AFX_MSG_MAP(CPage4)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage4 message handlers

BOOL CPage4::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetPos();	
	m_bFir=FALSE;
	SetPos();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage4::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_bFir)
	{
		SetPos();
	}	
}

void CPage4::SetPos()
{
	CRect clRect;
	GetClientRect(clRect);
	if(m_bFir)
	{
		clRect.left		= 0;
		clRect.right	= 1500;
		clRect.top		= 0;
		clRect.bottom	= 1500;
	}
	CRect drRect;

	float fHW=1.0f;
	if(clRect.Width()!=0)
	{
		fHW=clRect.Height()*1.0f/clRect.Width();
	}

	if(fHW<5/4.0f)
	{
		drRect.top		= clRect.top+2;
		drRect.bottom	= clRect.bottom-2;

		int iW = drRect.Height() * 4 / 5;

		drRect.left		= clRect.left	+ (clRect.Width() - iW) / 2;
		drRect.right	= clRect.right	- (clRect.Width() - iW) / 2;
	}
	else
	{
		drRect.left		= clRect.left	+ 2;
		drRect.right	= clRect.right	- 2;

		int iH = drRect.Width()*5/4;

		drRect.top		= clRect.top	+ (clRect.Height() - iH) / 2;
		drRect.bottom	= clRect.bottom	- (clRect.Height() - iH) / 2;
	}
	m_cCIE.MoveWindow(drRect);
}

void CPage4::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	CDC		*pDC;
	CWnd	*pWnd;
    pWnd	= GetDlgItem(IDC_CIE1976);
    pDC		= pWnd->GetDC();
	
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	
	CRect mRect;
	m_cCIE.GetWindowRect(mRect);

	if(m_pSpData != NULL)
	{
		m_pSpData->DrawCIE_UV(pDC, mRect);
	}

	// Do not call CPropertyPage::OnPaint() for painting messages
}

void CPage4::UpdateShow()
{
	Invalidate(FALSE);
}
