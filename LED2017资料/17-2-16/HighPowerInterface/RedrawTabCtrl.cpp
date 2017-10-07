// RedrawTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "RedrawTabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRedrawTabCtrl

DWORD CRedrawTabCtrl::s_dwCustomLook = 0;
CRedrawTabCtrl::CRedrawTabCtrl()
{
	m_bkcolor = (COLORREF)-1;
	m_nDrawType = BTC_NONE;
}

CRedrawTabCtrl::~CRedrawTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CRedrawTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CRedrawTabCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRedrawTabCtrl message handlers
void CRedrawTabCtrl::SetBKgndColor(COLORREF color)
{
	m_bkcolor = color;
	if(GetSafeHwnd())
	{
		Invalidate();
	}
}

extern int setting_sel;
BOOL CRedrawTabCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default		
//	return CTabCtrl::OnEraseBkgnd(pDC);
	CDC MemDC;
	CBitmap MemBitmap;

	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC, 228, 30);
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);

	if(0 == setting_sel)
	{
		CBitmap bitmapbk;
		bitmapbk.LoadBitmap(IDB_TabHeadSetChip);
		CBitmap* pOldBitmapSpan = MemDC.SelectObject(&bitmapbk);
	}
	else if(1 == setting_sel)
	{
		CBitmap bitmapbk;
		bitmapbk.LoadBitmap(IDB_TabHeadSetParam);
		CBitmap* pOldBitmapSpan = MemDC.SelectObject(&bitmapbk);
	}
	else if(2 == setting_sel)
	{
		CBitmap bitmapbk;
		bitmapbk.LoadBitmap(IDB_TabHeadSetLevel);
		CBitmap* pOldBitmapSpan = MemDC.SelectObject(&bitmapbk);
	}

	pDC->BitBlt(0, 0, 228, 30, &MemDC, 0, 0, SRCCOPY);

	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
	return true;
}


void CRedrawTabCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if((point.x >= 0) && (point.x <= 76) && (point.y >= 0) && (point.y <= 30))
	{
		setting_sel = 0;
	}
	else if((point.x > 76) && (point.x <= 152) && (point.y >= 0) && (point.y <= 30))
	{
		setting_sel = 1;
	}
	else if((point.x > 152) && (point.x <= 228) && (point.y >= 0) && (point.y <= 30))
	{
		setting_sel = 2;
	}
	CTabCtrl::OnLButtonDown(nFlags, point);
}


void CRedrawTabCtrl::Init()
{
	DWORD dwFlags = 0;
	dwFlags |= ETC_COLOR;
	dwFlags |= ETC_SELECTION;
	dwFlags |= ETC_GRADIENT;

	EnableDraw(BTC_TABS);
	EnableCustomLook(dwFlags);
}


bool CRedrawTabCtrl::EnableDraw(int nType)
{
	ASSERT((nType >= BTC_NONE) &&(nType <= BTC_ALL));

	if((nType < BTC_NONE) &&(nType > BTC_ALL))
	{
		return false;
	}

	m_nDrawType = nType;

	if(GetSafeHwnd())
	{
		if(m_nDrawType != BTC_NONE)
		{
			ModifyStyle(0, TCS_OWNERDRAWFIXED);
		}
		else
		{
			ModifyStyle(TCS_OWNERDRAWFIXED, 0);
		}
	}
	return true;
}

void CRedrawTabCtrl::EnableCustomLook(DWORD dwStyle)
{
	s_dwCustomLook = dwStyle;
}


void CRedrawTabCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// Do not call CTabCtrl::OnPaint() for painting messages
}

void CRedrawTabCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if((point.x >= 0) && (point.x <= 76) && (point.y >= 0) && (point.y <= 30))
	{
	}
	else if((point.x > 76) && (point.x <= 152) && (point.y >= 0) && (point.y <= 30))
	{
	}

	CTabCtrl::OnMouseMove(nFlags, point);
}
