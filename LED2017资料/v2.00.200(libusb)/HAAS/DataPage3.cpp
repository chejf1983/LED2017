// DataPage3.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DataPage3.h"
#include "SpectData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataPage3 property page

IMPLEMENT_DYNCREATE(CDataPage3, CPropertyPage)

CDataPage3::CDataPage3() : CPropertyPage(CDataPage3::IDD)
{
	//{{AFX_DATA_INIT(CDataPage3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bFir = TRUE;
	m_pSpData = NULL;
}

CDataPage3::~CDataPage3()
{
}

void CDataPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataPage3)
	DDX_Control(pDX, IDC_DRAW, m_cDraw);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CDataPage3)
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataPage3 message handlers

BOOL CDataPage3::OnInitDialog() 
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

void CDataPage3::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_bFir)
	{
		SetPos();
		ReDraw();
	}
}

void CDataPage3::SetPos()
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
	
	m_cDraw.MoveWindow(clRect);
}

void CDataPage3::ReDraw()
{
// 	CMuPolygonData temp;
// 	CSpectrumData::POLYGON_GetSele(CSpectrumData::m_iSelePolygon,temp);
// 
// 	BOOL bHaveXy = FALSE;
// 
// 	float x,y,fCCT;
// 	if(m_pSpData!=NULL)
// 	{
// 		bHaveXy = m_pSpData->Get_xy(x,y,fCCT);
// 	}
// 	else
// 	{
// 		bHaveXy = FALSE;
// 	}
// 
// 	m_cDraw.DrawPolygon(temp,bHaveXy,x,y,fCCT,m_pSpData->m_opData.m_bDxy);
}

void CDataPage3::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
// 	BOOL bR = CSpectrumData::POLYGON_Select();
// 	if(!bR)
// 		return;
// 
// 	ReDraw();

	CPropertyPage::OnLButtonDblClk(nFlags, point);
}
