// DataPage2.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DataPage2.h"
#include "SpectData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataPage2 property page

IMPLEMENT_DYNCREATE(CDataPage2, CPropertyPage)

CDataPage2::CDataPage2() : CPropertyPage(CDataPage2::IDD)
{
	//{{AFX_DATA_INIT(CDataPage2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bFir = TRUE;

	m_fx = 0.430f;
	m_fy = 0.480f;
	m_fCCT = 2856.0f;

	m_bHaveData = FALSE;
}

CDataPage2::~CDataPage2()
{
}

void CDataPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataPage2)
	DDX_Control(pDX, IDC_CIE, m_cCIE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CDataPage2)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataPage2 message handlers

BOOL CDataPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	SetPos();
	m_bFir = FALSE;
	SetPos();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDataPage2::SetPos()
{
	CRect clRect;
	GetClientRect(clRect);

	m_cCIE.MoveWindow(clRect);
}

void CDataPage2::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_bFir)
		SetPos();
}

void CDataPage2::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CPropertyPage::OnPaint() for painting messages
	CPen *pOldPen;
	CPen Pen1,Pen2;
	Pen1.CreatePen(PS_SOLID,1,RGB(255,255,0));
	Pen2.CreatePen(PS_SOLID,2,RGB(0,0,0));
	CDC *pDC;
	CWnd *pWnd;
    pWnd=GetDlgItem(IDC_CIE);
    pDC=pWnd->GetDC();
	
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	
	CRect mRect,xRect;
	m_cCIE.GetWindowRect(mRect);
	
	xRect.left	= (int)(mRect.Width() * 0.0f / 100);
	xRect.right	= (int)(mRect.Width() - mRect.Width() * 1 / 100.0f);
	xRect.top	= (int)(mRect.Height() * 0 / 11.0f);
	xRect.bottom= (int)(mRect.Height()-mRect.Height() * 1 / 100.0f);
	
	pOldPen		= pDC->SelectObject(&Pen1);
	
	if(0)
	{
		pDC->MoveTo(xRect.left,	xRect.top);
		pDC->LineTo(xRect.left,	xRect.bottom);
		pDC->LineTo(xRect.right,xRect.bottom);
		pDC->LineTo(xRect.right,xRect.top);
	}
	
	pDC->SelectObject(&Pen2);
	pDC->SetTextAlign(TA_RIGHT);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0,0,255));
	CString sTemp;
	sTemp.Format("x = %.4f y = %.4f",m_fx, m_fy);
	
	if(m_bHaveData)
	{
		pDC->TextOut(xRect.right - xRect.Width() / 20,xRect.top + xRect.Height() / 20, sTemp);
	}
	
	if(m_fCCT > 1000 && m_fCCT < 100000)
	{
		sTemp.Format("CCT = %.0fK", m_fCCT);
	}
	else if(m_fCCT <= 1000)
	{
		sTemp.Format("CCT <= 1000K");
	}
	else
	{
		sTemp.Format("CCT >= 100000K");
	}
	
	if(m_bHaveData)
	{
		pDC->TextOut(xRect.right-xRect.Width()/10, xRect.top+xRect.Height()/8,sTemp);
	}
	
	int xx,yy;
	
	xx	= (int)(xRect.left+m_fx*xRect.Width()/0.8f+0.5f);
	yy	= (int)(xRect.bottom-m_fy*xRect.Height()/0.9f+0.5f);
	
	int x,y;
	
	x	= (int)(xRect.left	 + (m_fx + 0.1f) * xRect.Width() + 0.5f);
	y	= (int)(xRect.bottom - (m_fy + 0.1f) * xRect.Height() *10 / 11 + 0.5f);
	
	int iM = 5;
	if(m_bHaveData)
	{
		pDC->MoveTo(x-iM,y);
		pDC->LineTo(x+iM,y);
		pDC->MoveTo(x,y-iM);
		pDC->LineTo(x,y+iM);
	}
	
// 	xRect.left	= (int)(mRect.Width()/14.5f+0.5f);
// 	xRect.right	= (int)(mRect.Width()-mRect.Width()/28.5f+0.5f);
// 	xRect.top	= (int)(mRect.Height()/40.0f+0.5f);
// 	xRect.bottom= (int)(mRect.Height()-mRect.Height()/12.0f+0.5f);
// 	
// 	pOldPen=pDC->SelectObject(&Pen1);
// 	
// 	if(0)
// 	{
// 		pDC->MoveTo(xRect.left,xRect.top);
// 		pDC->LineTo(xRect.left,xRect.bottom);
// 		pDC->LineTo(xRect.right,xRect.bottom);
// 		pDC->LineTo(xRect.right,xRect.top);
// 	}
// 	
// 	pDC->SelectObject(&Pen2);
// 	pDC->SetTextAlign(TA_RIGHT);
// 	pDC->SetBkMode(TRANSPARENT);
// 	pDC->SetTextColor(RGB(233,255,255));
// 	CString strTemp;
// 	if(m_bHaveData)
// 	{
// 		strTemp.Format("x = %.4f y = %.4f",m_fx,m_fy);
// 		pDC->TextOut(xRect.right-xRect.Width()/20,
// 			xRect.top+xRect.Height()/20,strTemp);
// 	}
// 
// 	if(m_bHaveData)
// 	{
// 		strTemp.Format("Tc = %.0fK",m_fCCT);
// 		pDC->TextOut(xRect.right-xRect.Width()/10,
// 			xRect.top+xRect.Height()/8,strTemp);
// 	}
// 
// 	int x,y;
// 
// 	x=(int)(xRect.left+m_fx*xRect.Width()/0.8f+0.5f);
// 	y=(int)(xRect.bottom-m_fy*xRect.Height()/0.9f+0.5f);
// 	
// 	if(m_bHaveData)
// 	{
// 		int iM = 7;
// 		pDC->MoveTo(x-iM,y);
// 		pDC->LineTo(x+iM,y);
// 		pDC->MoveTo(x,y-iM);
// 		pDC->LineTo(x,y+iM);
// 	}

	pDC->SelectObject(pOldPen);
}

void CDataPage2::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CPropertyPage::OnLButtonDblClk(nFlags, point);
}
