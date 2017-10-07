// ColorDemo.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "ColorDemo.h"

// CColorDemo

IMPLEMENT_DYNAMIC(CColorDemo, CStatic)

CColorDemo::CColorDemo()
{

}

CColorDemo::~CColorDemo()
{

}


BEGIN_MESSAGE_MAP(CColorDemo, CStatic)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CColorDemo 消息处理程序




void CColorDemo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CStatic::OnPaint()
	int iRedundant = 0;
	CPoint centerPoint(0,0);
	CBrush brush;
	HGDIOBJ hOldObject;
	CRect rect;
	
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(160, 160, 160));

	GetClientRect(&rect);    
    //CBrush memBrush;
    //memBrush.CreateSolidBrush(::GetSysColor(COLOR_3DFACE));

    //HGDIOBJ hOld;
    //hOld = dc.SelectObject(&memBrush);
    //dc.SelectObject(GetStockObject(NULL_PEN));
    //dc.Rectangle(rect);
    //dc.DrawEdge(rect, BDR_RAISED, BF_RECT);

    hOldObject = dc.SelectObject(&m_newFont);
    dc.SelectObject(&pen);
	CSize sizeTextExtent = dc.GetOutputTextExtent("合格", 2);

	if (rect.Width() > rect.Height())
	{
		if (rect.Width() > 4 * rect.Height())
		{
			/// square in a line, text on the right
			/// width > 4 * height
			// 11 12 13 14
			CRect rect11 = rect, rect12 = rect;
			CRect rect13 = rect, rect14 = rect;
	
			// rect11	111 112
			rect11.right = rect11.left + rect.Width()/4;

			CRect rect111 = rect11, rect112 = rect11;
			rect111.right = rect111.left + rect11.Width()/2;
			rect112.left = rect111.right;
	
			iRedundant = rect111.Width() - rect111.Height();
			iRedundant = iRedundant > 0 ? iRedundant : (iRedundant * -1);
			if (rect111.Width() > rect111.Height())
			{
				// The leftmost square
				rect111.right -= iRedundant;
			}
			else
			{
				// The center square
				rect111.top += iRedundant / 2;
				rect111.bottom = rect111.top + rect111.Width();
			}

			rect112.left = rect111.right;
			rect112.top = rect111.top;
			rect112.bottom = rect111.bottom;

			rect111.DeflateRect(rect111.Width() / 6, rect111.Height() / 6);
			brush.CreateSolidBrush(g_ColorGood);
			dc.SelectObject(&brush);
			dc.Ellipse(&rect111);

			dc.SetBkMode(TRANSPARENT);
			dc.TextOut(rect112.left, (rect112.top + rect112.bottom)/2 - sizeTextExtent.cy/2, "合格");
			brush.Detach();

			// rect12	121 122
			rect12.left = rect11.right;
			rect12.right = rect12.left + rect.Width()/4;

			CRect rect121 = rect12, rect122 = rect12;
			rect121.right = rect121.left + rect12.Width()/2;
			rect122.left = rect121.right;
	
			iRedundant = rect121.Width() - rect121.Height();
			iRedundant = iRedundant > 0 ? iRedundant : (iRedundant * -1);
			if (rect121.Width() > rect121.Height())
			{
				// The leftmost square
				rect121.right -= iRedundant;
			}
			else
			{
				// The center square
				rect121.top += iRedundant / 2;
				rect121.bottom = rect121.top + rect121.Width();
			}

			rect122.left = rect121.right;
			rect122.top = rect121.top;
			rect122.bottom = rect121.bottom;

			rect121.DeflateRect(rect121.Width() / 6, rect121.Height() / 6);
			brush.CreateSolidBrush(g_ColorBad);
			dc.SelectObject(&brush);
			dc.Ellipse(&rect121);

			dc.SetBkMode(TRANSPARENT);
			dc.TextOut(rect122.left, (rect122.top + rect122.bottom)/2 - sizeTextExtent.cy/2, "不合格");
			brush.Detach();

			// rect13	131 132
			rect13.left = rect12.right;
			rect13.right = rect13.left + rect.Width()/4;
	
			CRect rect131 = rect13, rect132 = rect13;
			rect131.right = rect131.left + rect13.Width()/2;
			rect132.left = rect131.right;
	
			iRedundant = rect131.Width() - rect131.Height();
			iRedundant = iRedundant > 0 ? iRedundant : (iRedundant * -1);
			if (rect131.Width() > rect131.Height())
			{
				// The leftmost square
				rect131.right -= iRedundant;
			}
			else
			{
				// The center square
				rect131.top += iRedundant / 2;
				rect131.bottom = rect131.top + rect131.Width();
			}

			rect132.left = rect131.right;
			rect132.top = rect131.top;
			rect132.bottom = rect131.bottom;
	
			rect131.DeflateRect(rect131.Width() / 6, rect131.Height() / 6);
			brush.CreateSolidBrush(g_ColorInvalid);
			dc.SelectObject(&brush);
			dc.Ellipse(&rect131);

			dc.SetBkMode(TRANSPARENT);
			dc.TextOut(rect132.left, (rect132.top + rect132.bottom)/2 - sizeTextExtent.cy/2, "测试失败");
			brush.Detach();

			// rect14	141 142
			rect14.left = rect13.right;
			rect14.right = rect14.left + rect.Width()/4;
	
			CRect rect141 = rect14, rect142 = rect14;
			rect141.right = rect141.left + rect14.Width()/2;
			rect142.left = rect141.right;
	
			iRedundant = rect141.Width() - rect141.Height();
			iRedundant = iRedundant > 0 ? iRedundant : (iRedundant * -1);
			if (rect141.Width() > rect141.Height())
			{
				// The leftmost square
				rect141.right -= iRedundant;
			}
			else
			{
				// The center square
				rect141.top += iRedundant / 2;
				rect141.bottom = rect141.top + rect141.Width();
			}

			rect142.left = rect141.right;
			rect142.top = rect141.top;
			rect142.bottom = rect141.bottom;
	
			rect141.DeflateRect(rect141.Width() / 6, rect141.Height() / 6);
			brush.CreateSolidBrush(g_ColorNotTest);
			dc.SelectObject(&brush);
			dc.Ellipse(&rect141);

			dc.SetBkMode(TRANSPARENT);
			dc.TextOut(rect142.left, (rect142.top + rect142.bottom)/2 - sizeTextExtent.cy/2, "未测试");
			brush.Detach();
		}
		else
		{
			/// Four square divided in tow row, text on the right 
			/// height < width <= 4 * height
            // 00
			// 11 12
			// 13 14
            int iLeftAdd = 15, iRightAdd = -8;
            CRect rect00 = rect;

            rect00.right = rect.left +  rect.Width() / 2;
            rect00.bottom = rect00.top + rect.Height() / 5;

            CRect rect000 = rect00, rect001= rect00; 
            rect000.right = rect000.left + rect000.Height();
            rect000.DeflateRect(iLeftAdd, 0, iRightAdd, 0);
            int iMinDistance = rect000.Width() > rect000.Height() ? rect000.Height() : rect000.Width();
            iMinDistance /= 2;
            rect001.left = rect000.right + sizeTextExtent.cx;

            brush.CreateSolidBrush(g_ColorGood);
            dc.SelectObject(&brush);
            dc.Ellipse(rect000.CenterPoint().x - iMinDistance,
                rect000.CenterPoint().y - iMinDistance,
                rect000.CenterPoint().x + iMinDistance,
                rect000.CenterPoint().y + iMinDistance);

            dc.SetBkMode(TRANSPARENT);
            dc.SetTextAlign(TA_LEFT);
            dc.TextOut(rect001.left, (rect001.top + rect001.bottom)/2 - sizeTextExtent.cy/2, "合格");
            brush.Detach();


            rect00.top =  rect00.bottom;
            rect00.bottom = rect00.top + rect.Height() / 5;

            rect000 = rect00;
            rect001= rect00; 
            rect000.right = rect000.left + rect000.Height();
            rect000.DeflateRect(iLeftAdd, 0, iRightAdd, 0);
            iMinDistance = rect000.Width() > rect000.Height() ? rect000.Height() : rect000.Width();
            iMinDistance /= 2;
            rect001.left = rect000.right + sizeTextExtent.cx;

            brush.CreateSolidBrush(g_ColorBad);
            dc.SelectObject(&brush);
            dc.Ellipse(rect000.CenterPoint().x - iMinDistance,
                rect000.CenterPoint().y - iMinDistance,
                rect000.CenterPoint().x + iMinDistance,
                rect000.CenterPoint().y + iMinDistance);

            dc.SetBkMode(TRANSPARENT);
            dc.SetTextAlign(TA_LEFT);
            dc.TextOut(rect001.left, (rect001.top + rect001.bottom)/2 - sizeTextExtent.cy/2, "不合格(超限值)");
            brush.Detach();


            rect00.top =  rect00.bottom;
            rect00.bottom = rect00.top + rect.Height() / 5;

            rect000 = rect00;
            rect001= rect00; 
            rect000.right = rect000.left + rect000.Height();
            rect000.DeflateRect(iLeftAdd, 0, iRightAdd, 0);
            iMinDistance = rect000.Width() > rect000.Height() ? rect000.Height() : rect000.Width();
            iMinDistance /= 2;
            rect001.left = rect000.right + sizeTextExtent.cx;


            brush.CreateSolidBrush(g_ColorBad_Codi);
            dc.SelectObject(&brush);
            dc.Ellipse(rect000.CenterPoint().x - iMinDistance,
                rect000.CenterPoint().y - iMinDistance,
                rect000.CenterPoint().x + iMinDistance,
                rect000.CenterPoint().y + iMinDistance);

            dc.SetBkMode(TRANSPARENT);
            dc.SetTextAlign(TA_LEFT);
            dc.TextOut(rect001.left, (rect001.top + rect001.bottom)/2 - sizeTextExtent.cy/2, "不合格(未亮或无灯)");
            brush.Detach();


            rect00.top =  rect00.bottom;
            rect00.bottom = rect00.top + rect.Height() / 5;

            rect000 = rect00;
            rect001= rect00; 
            rect000.right = rect000.left + rect000.Height();
            rect000.DeflateRect(iLeftAdd, 0, iRightAdd, 0);
            iMinDistance = rect000.Width() > rect000.Height() ? rect000.Height() : rect000.Width();
            iMinDistance /= 2;
            rect001.left = rect000.right + sizeTextExtent.cx;


            brush.CreateSolidBrush(g_ColorInvalid);
            dc.SelectObject(&brush);
            dc.Ellipse(rect000.CenterPoint().x - iMinDistance,
                rect000.CenterPoint().y - iMinDistance,
                rect000.CenterPoint().x + iMinDistance,
                rect000.CenterPoint().y + iMinDistance);

            dc.SetBkMode(TRANSPARENT);
            dc.SetTextAlign(TA_LEFT);
            dc.TextOut(rect001.left, (rect001.top + rect001.bottom)/2 - sizeTextExtent.cy/2, "测试失败");
            brush.Detach();

            rect00.top =  rect00.bottom;
            rect00.bottom = rect00.top + rect.Height() / 5;

            rect000 = rect00;
            rect001= rect00; 
            rect000.right = rect000.left + rect000.Height();
            rect000.DeflateRect(iLeftAdd, 0, iRightAdd, 0);
            iMinDistance = rect000.Width() > rect000.Height() ? rect000.Height() : rect000.Width();
            iMinDistance /= 2;
            rect001.left = rect000.right + sizeTextExtent.cx;


            brush.CreateSolidBrush(g_ColorNotTest);
            dc.SelectObject(&brush);
            dc.Ellipse(rect000.CenterPoint().x - iMinDistance,
                rect000.CenterPoint().y - iMinDistance,
                rect000.CenterPoint().x + iMinDistance,
                rect000.CenterPoint().y + iMinDistance);

            dc.SetBkMode(TRANSPARENT);
            dc.SetTextAlign(TA_LEFT);
            dc.TextOut(rect001.left, (rect001.top + rect001.bottom)/2 - sizeTextExtent.cy/2, "未测试");
            brush.Detach();
		}
	}
	else
	{
		/// Four square divided in tow row, text at the bottom
		/// width < height
		// 11 12
		// 13 14
		CRect rect11 = rect, rect12 = rect;
		CRect rect13 = rect, rect14 = rect;

		// rect11 111
		//        112
		rect11.right = rect11.left + rect.Width() / 2;
		rect11.bottom = rect11.top + rect.Height() / 2;
		CRect rect111 = rect11, rect112 = rect11;
		rect112.top = rect112.bottom - rect11.Height()/4;
		rect111.bottom = rect112.top;
		int iMinDistance = rect111.Width() > rect111.Height() ? rect111.Height() : rect111.Width();
		iMinDistance /= 2;

		brush.CreateSolidBrush(g_ColorGood);
		dc.SelectObject(&brush);
		dc.Ellipse(rect111.CenterPoint().x - iMinDistance,
			rect111.CenterPoint().y - iMinDistance,
			rect111.CenterPoint().x + iMinDistance,
			rect111.CenterPoint().y + iMinDistance);

		dc.SetBkMode(TRANSPARENT);
		dc.SetTextAlign(TA_CENTER);
		dc.TextOut(rect112.CenterPoint().x, (rect112.top + rect112.bottom)/2 - sizeTextExtent.cy/2, "合格");
		brush.Detach();


		// rect12 121
		//        122
		rect12.left = rect11.right;
		rect12.bottom = rect12.top + rect.Height() / 2;
		CRect rect121 = rect12, rect122 = rect12;
		rect122.top = rect122.bottom - rect12.Height()/4;
		rect121.bottom = rect122.top;
		iMinDistance = rect121.Width() > rect121.Height() ? rect121.Height() : rect121.Width();
		iMinDistance /= 2;

		brush.CreateSolidBrush(g_ColorBad);
		hOldObject = dc.SelectObject(&brush);
		dc.Ellipse(rect121.CenterPoint().x - iMinDistance,
			rect121.CenterPoint().y - iMinDistance,
			rect121.CenterPoint().x + iMinDistance,
			rect121.CenterPoint().y + iMinDistance);

		dc.SetBkMode(TRANSPARENT);
		dc.SetTextAlign(TA_CENTER);
		dc.TextOut(rect122.CenterPoint().x, (rect122.top + rect122.bottom)/2 - sizeTextExtent.cy/2, "不合格");
		brush.Detach();


		// rect13 131
		//        132
		rect13.right = rect13.left + rect.Width() / 2;
		rect13.top = rect11.bottom;
		CRect rect131 = rect13, rect132 = rect13;
		rect132.top = rect132.bottom - rect13.Height()/4;
		rect131.bottom = rect132.top;
		iMinDistance = rect131.Width() > rect131.Height() ? rect131.Height() : rect131.Width();
		iMinDistance /= 2;

		brush.CreateSolidBrush(g_ColorInvalid);
		dc.SelectObject(&brush);
		dc.Ellipse(rect131.CenterPoint().x - iMinDistance,
			rect131.CenterPoint().y - iMinDistance,
			rect131.CenterPoint().x + iMinDistance,
			rect131.CenterPoint().y + iMinDistance);

		dc.SetBkMode(TRANSPARENT);
		dc.SetTextAlign(TA_CENTER);
		dc.TextOut(rect132.CenterPoint().x, (rect132.top + rect132.bottom)/2 - sizeTextExtent.cy/2, "测试失败");
		brush.Detach();


		// rect14 141
		//        142
		rect14.left = rect13.right;
		rect14.top = rect12.bottom;
		CRect rect141 = rect14, rect142 = rect14;
		rect142.top = rect142.bottom - rect14.Height()/4;
		rect141.bottom = rect142.top;
		iMinDistance = rect141.Width() > rect141.Height() ? rect141.Height() : rect141.Width();
		iMinDistance /= 2;

		brush.CreateSolidBrush(g_ColorNotTest);
		dc.SelectObject(&brush);
		dc.Ellipse(rect141.CenterPoint().x - iMinDistance,
			rect141.CenterPoint().y - iMinDistance,
			rect141.CenterPoint().x + iMinDistance,
			rect141.CenterPoint().y + iMinDistance);

		dc.SetBkMode(TRANSPARENT);
		dc.SetTextAlign(TA_CENTER);
		dc.TextOut(rect142.CenterPoint().x, (rect142.top + rect142.bottom)/2 - sizeTextExtent.cy/2, "未测试");
		brush.Detach();

	}

	dc.SelectObject(hOldObject);
}


int CColorDemo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_newFont.CreateFont(-16,0,0,0,500,FALSE,FALSE,0,
		GB2312_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"宋体");

	return 0;
}
