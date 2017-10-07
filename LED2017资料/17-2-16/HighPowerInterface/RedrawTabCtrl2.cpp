// RedrawTabCtrl2.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "RedrawTabCtrl2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRedrawTabCtrl2

CRedrawTabCtrl2::CRedrawTabCtrl2()
{
}

CRedrawTabCtrl2::~CRedrawTabCtrl2()
{
}


BEGIN_MESSAGE_MAP(CRedrawTabCtrl2, CTabCtrl)
	//{{AFX_MSG_MAP(CRedrawTabCtrl2)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRedrawTabCtrl2 message handlers
extern int setpara_sel;
BOOL CRedrawTabCtrl2::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default	
//	return CTabCtrl::OnEraseBkgnd(pDC);
	CDC MemDC;
	CBitmap MemBitmap;

	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC, 180, 30);
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);

	if(0 == setpara_sel)
	{
		CBitmap bitmapbk;
		bitmapbk.LoadBitmap(IDB_TabHeadChip1);
		CBitmap* pOldBitmapSpan = MemDC.SelectObject(&bitmapbk);
	}
	if(1 == setpara_sel)
	{
		CBitmap bitmapbk;
		bitmapbk.LoadBitmap(IDB_TabHeadChip2);
		CBitmap* pOldBitmapSpan = MemDC.SelectObject(&bitmapbk);
	}
	if(2 == setpara_sel)
	{
		CBitmap bitmapbk;
		bitmapbk.LoadBitmap(IDB_TabHeadChip3);
		CBitmap* pOldBitmapSpan = MemDC.SelectObject(&bitmapbk);
	}

	pDC->BitBlt(0, 0, 180, 30, &MemDC, 0, 0, SRCCOPY);

	MemBitmap.DeleteObject();
	MemDC.DeleteDC();

	return true;
}

void CRedrawTabCtrl2::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CTabCtrl::OnPaint() for painting messages
}

void CRedrawTabCtrl2::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if((point.x >= 0) && (point.x <= 60) && (point.y >= 0) && (point.y <= 30))
	{
		setpara_sel = 0;
	}
	else if((point.x > 60) && (point.x <= 120) && (point.y >= 0) && (point.y <= 30))
	{
		setpara_sel = 1;
	}
	else if((point.x > 120) && (point.x <= 180) && (point.y >= 0) && (point.y <= 30))
	{
		setpara_sel = 2;
	}
	CTabCtrl::OnLButtonDown(nFlags, point);
}

