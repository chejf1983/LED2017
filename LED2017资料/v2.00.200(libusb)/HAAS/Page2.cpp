// Page2.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Page2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage2 dialog
extern CString g_strCurPath;

IMPLEMENT_DYNCREATE(CPage2, CDialog);

CPage2::CPage2(CWnd* pParent /*=NULL*/)
	: CDialog(CPage2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPage2)
	//}}AFX_DATA_INIT
	m_bFir=TRUE;
	m_pSpData=NULL;
}


void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage2)
	DDX_Control(pDX, IDC_CIE1931, m_cCIE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage2, CDialog)
	//{{AFX_MSG_MAP(CPage2)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage2 message handlers

BOOL CPage2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetPos();	
	m_bFir=FALSE;
	SetPos();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage2::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_bFir)
	{
		SetPos();
	}	
}

void CPage2::SetPos()
{
	CRect clRect;
	GetClientRect(clRect);
	if(m_bFir)
	{
		clRect.left		= 0;
		clRect.right	= 1000;
		clRect.top		= 0;
		clRect.bottom	= 1000;
	}
	CRect drRect;

	float fHW = 1.0f;
	if(clRect.Width()!=0)
	{
		fHW = clRect.Height() * 1.0f / clRect.Width();
	}
	if(fHW<5 / 4.0f)
	{
		drRect.top		= clRect.top	+ 2;
		drRect.bottom	= clRect.bottom	- 2;

		int iW = drRect.Height() * 10 / 11;

		drRect.left		= clRect.left+(clRect.Width()-iW)/2;
		drRect.right	= clRect.right-(clRect.Width()-iW)/2;
	}
	else
	{
		drRect.left	 = clRect.left  + 2;
		drRect.right = clRect.right - 2;

		int iH = drRect.Width() * 11 / 10;

		drRect.top		= clRect.top	+ (clRect.Height() - iH) / 2;
		drRect.bottom	= clRect.bottom	- (clRect.Height() - iH) / 2;
	}
	m_cCIE.MoveWindow(drRect);
//	m_cDraw.MoveWindow(drRect);
}

void CPage2::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
/*	CRect Rect1,Rect2;
	GetClientRect(&Rect1);
	ClientToScreen(&Rect1);
	m_cDraw.GetClientRect(&Rect2);
	m_cDraw.ClientToScreen(&Rect2);
	
	CRect mRect;      // Placeholder rectangle
	m_cDraw.GetWindowRect( &mRect );
	ScreenToClient( &mRect );
	
	CString strTemp,strPathName;

	strPathName		= g_strCurPath+"CIE1931.bmp";

	char *pBuffer	= (char *)(LPCTSTR)strPathName;

	m_bitmapEx.Load(pBuffer);
	m_bitmapEx.Scale2(mRect.Width(),mRect.Height());
	m_bitmapEx.Draw(dc.m_hDC,mRect.left,mRect.top);

	//»­ÇøÓò

	CFont *pOldFont;
	CFont pFont1;
	CFont pFont2;

	pFont1.CreateFont(mRect.Height()/18,0,0,0,500,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"MS Sans Serif");

	pFont2.CreateFont(mRect.Height()/18,0,0,0,500,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"MS Sans Serif");

	CPen  *pOldPen;
	CPen  pPen1;
	CPen  pPen2;
	CPen  pPen3;

	pPen1.CreatePen(PS_SOLID,1,RGB(0,255,128));
	pPen2.CreatePen(PS_SOLID,1,RGB(255,0,0));
	pPen3.CreatePen(PS_SOLID,1,RGB(255,255,0));

	if (dc.GetSafeHdc() == NULL)
	{
		CClientDC dc(this);
		dc.CreateCompatibleDC(&dc) ;
		m_bitmapPlot.CreateCompatibleBitmap(&dc, m_nClientWidth, m_nClientHeight) ;
		m_pbitmapOldPlot = dc.SelectObject(&m_bitmapPlot) ;
	}
	int Wn=m_nClientWidth/40;
	int Hn=m_nClientHeight/35;

	dc.SetBkMode(TRANSPARENT);
	pOldFont=dc.SelectObject(&pFont1);
	pOldPen	=dc.SelectObject(&pPen1);

	dc.SelectObject(pOldFont);
	dc.SelectObject(pOldPen);
*/	
	CDC *pDC;
	CWnd *pWnd;
    pWnd=GetDlgItem(IDC_CIE1931);
    pDC = pWnd->GetDC();
	
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	
	CRect mRect;
	m_cCIE.GetWindowRect(mRect);

	if(m_pSpData!=NULL)
	{
		m_pSpData->DrawCIE(pDC, mRect);
	}

	// Do not call CPropertyPage::OnPaint() for painting messages
}

void CPage2::UpdateShow()
{
	Invalidate(FALSE);
}
