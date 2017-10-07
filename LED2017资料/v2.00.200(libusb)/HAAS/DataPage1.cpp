// DataPage1.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DataPage1.h"
#include "SpectData.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataPage1 property page
//CMySpecDoc *g_pDoc;
extern int g_iSeleTc;
extern int g_iSDCM1;
extern int g_iSDCM2;

IMPLEMENT_DYNCREATE(CDataPage1, CPropertyPage)

CDataPage1::CDataPage1() : CPropertyPage(CDataPage1::IDD)
{
	//{{AFX_DATA_INIT(CDataPage1)
	//}}AFX_DATA_INIT

	m_bFir = TRUE;
}

CDataPage1::~CDataPage1()
{
}

void CDataPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataPage1)
	DDX_Control(pDX, IDC_SDCM, m_cSDCM);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CDataPage1)
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataPage1 message handlers

BOOL CDataPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	SetPos();
	ReDraw();
	m_bFir = FALSE;

	SetPos();
	ReDraw();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDataPage1::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_bFir)
	{
		SetPos();
		ReDraw();
	}
}

void CDataPage1::SetPos()
{
	CRect clRect;
	GetClientRect(clRect);
	if(m_bFir)
	{
		clRect.left = 0;
		clRect.right = 1000;
		clRect.top = 0;
		clRect.bottom = 1000;
	}

	m_cSDCM.MoveWindow(clRect);
}

void CDataPage1::ReDraw()
{
	if(m_pSpData.m_fRelSpect.GetSize() > 0)
	{
		m_cSDCM.DrawSDCM(m_pSpData,g_iSeleTc,g_iSDCM1,g_iSDCM2);
	}
	else
	{
		m_cSDCM.DrawSDCM(m_pSpData,0,5,6);
	}
}

void CDataPage1::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	ReDraw();

	CPropertyPage::OnLButtonDblClk(nFlags, point);
}
