// MyCheckLED.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "MyCheckLED.h"
#include <math.h> 

// CMyCheckLED

CToolTipEx CMyCheckLED::m_cToolTipEx;

IMPLEMENT_DYNAMIC(CMyCheckLED, CStatic)

CMyCheckLED::CMyCheckLED()
{
	m_iCount	= 10;
	m_bChecked	= FALSE;
	m_bMouseIn	= FALSE;
	m_color		= RGB(200, 200, 200);
	m_colorHighLight	= RGB(230, 230, 230);
	m_colorSelected		= RGB(150, 150, 150);
}

CMyCheckLED::~CMyCheckLED()
{
}


BEGIN_MESSAGE_MAP(CMyCheckLED, CStatic)
	ON_WM_PAINT()
	ON_CONTROL_REFLECT(STN_CLICKED, &CMyCheckLED::OnStnClicked)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CMyCheckLED 消息处理程序



void CMyCheckLED::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	CRect rect;
	GetClientRect(&rect);

	// Get square in center
	if (rect.Width() < rect.Height())
	{
		int iDeflate = (rect.Height() - rect.Width()) / 2;
		rect.top	+= iDeflate;
		rect.bottom -= iDeflate;
	}
	else
	{
		int iDeflate = (rect.Width() - rect.Height()) / 2;
		rect.left	+= iDeflate;
		rect.right	-= iDeflate;
	}

	// Draw edge
	//dc.Draw3dRect(&rect, RGB(255, 255, 255), RGB(200 ,200 ,200));
	if (m_bMouseIn)
	{
		dc.DrawEdge(&rect, BDR_SUNKENOUTER, BF_RECT);
	}
	else
	{
		dc.DrawEdge(&rect, BDR_RAISEDOUTER, BF_RECT);
	}
	rect.DeflateRect(2, 2);

	COLORREF colorTemp;
	colorTemp = m_bMouseIn ? m_colorHighLight : m_color;
	if (m_bChecked)
	{
		colorTemp = m_colorSelected;
	}
	CBrush brush(colorTemp);
	HGDIOBJ hOld = dc.SelectObject(&brush);
	CPen pen(PS_NULL, 1, RGB(0, 0, 0));
	dc.SelectObject(&pen);
	dc.Ellipse(&rect);
	
	if (m_bChecked)
	{
		dc.SetBkMode(TRANSPARENT);
		CBrush brush2(HS_DIAGCROSS, RGB(10, 10, 10));
		dc.SelectObject(&brush2);
		dc.Ellipse(&rect);
	}

	dc.SelectObject(hOld);
}

void CMyCheckLED::SetColor(COLORREF color)
{
	m_color				= color;
	m_colorHighLight	= RGB(GetRValue(m_color)*6/5 , GetGValue(m_color)*6/5, GetBValue(m_color)*6/5);
	m_colorSelected		= RGB(GetRValue(m_color)*3/4, GetGValue(m_color)*3/4, GetBValue(m_color)*3/4);

	Invalidate(TRUE);
}

BOOL CMyCheckLED::GetCheck()
{
	return m_bChecked;
}

BOOL CMyCheckLED::SetCheck(BOOL bCheck)
{
	m_bChecked = bCheck;
	Invalidate(TRUE);

	return bCheck;
}

void CMyCheckLED::OnStnClicked()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_bChecked = !m_bChecked;
	//SetFocus();
	//Invalidate(TRUE);
}


void CMyCheckLED::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!m_bMouseIn)
	{
        m_bMouseIn	= TRUE;   

        TRACKMOUSEEVENT mouseEvent; 

        mouseEvent.cbSize		= sizeof(TRACKMOUSEEVENT);   
        mouseEvent.hwndTrack	= GetSafeHwnd();   
        mouseEvent.dwFlags	= TME_LEAVE;

        ::_TrackMouseEvent(&mouseEvent);
		Invalidate(TRUE);
	}

	CStatic::OnMouseMove(nFlags, point);
}


void CMyCheckLED::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bMouseIn)   
    {
        m_bMouseIn = FALSE;
		Invalidate(TRUE);
    }

	CStatic::OnMouseLeave();
}


void CMyCheckLED::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (1 == nIDEvent)
	{
		if (m_iCount != 10)
		{
			KillTimer(1);
		}

		m_color = m_colorHighLight * (5 + m_iCount) / (6 + m_iCount);
		m_iCount --;
		Invalidate(TRUE);

		if (0 == m_iCount)
		{
			m_iCount = 10;
			KillTimer(1);
		}
	}

	CStatic::OnTimer(nIDEvent);
}


int CMyCheckLED::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


BOOL CMyCheckLED::SetTooltip(CString strTooltipText)
{
    if(!GetSafeHwnd())   
    {   
        return FALSE;//如果按钮没有创建，则返失败    
    }   
    if(!m_cToolTipEx.GetSafeHwnd())   
    {   
        m_cToolTipEx.Create(GetParent());   
    } 
   
    m_cToolTipEx.DelTool(this);
    m_cToolTipEx.AddTool(this,strTooltipText);
	m_cToolTipEx.SetMaxTipWidth(300);

    return TRUE;
}   

BOOL CMyCheckLED::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
    if(m_cToolTipEx.GetSafeHwnd())   
    {
        m_cToolTipEx.RelayEvent(pMsg);   
    }   

	return CStatic::PreTranslateMessage(pMsg);
}
