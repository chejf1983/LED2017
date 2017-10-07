// HistogramGraphCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "HistogramGraphCtrl.h"
#include "LAT2000Doc.h"

// CHistogramGraphCtrl
COLORREF m_AllColor[DISTRIBUTION_NUM] = {RGB(128, 0, 255), RGB(0, 128, 255), RGB(0, 0, 255),
                                          RGB(255, 0, 255), RGB(128, 255, 128), RGB(255, 0, 0)};
IMPLEMENT_DYNAMIC(CHistogramGraphCtrl, CStatic)

CHistogramGraphCtrl::CHistogramGraphCtrl()
{
    m_fontHor.CreateFont(-12, 0, 0, 0, 500, FALSE, FALSE, 0,
        GB2312_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_MODERN,"宋体");
    m_fontTitle.CreateFont(20, 0, 0, 0, 500, FALSE, FALSE, 0,
        GB2312_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_MODERN,"宋体");
}

CHistogramGraphCtrl::~CHistogramGraphCtrl()
{
}


BEGIN_MESSAGE_MAP(CHistogramGraphCtrl, CStatic)
    ON_WM_PAINT()
END_MESSAGE_MAP()



// CHistogramGraphCtrl 消息处理程序




void CHistogramGraphCtrl::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CStatic::OnPaint()
    CRect rectClient;
    GetClientRect(&rectClient);

    CDC memDC;
    CBitmap MemBitmap;
    memDC.CreateCompatibleDC(NULL);
    MemBitmap.CreateCompatibleBitmap(&dc, rectClient.Width(), rectClient.Height());
    CBitmap * pOldBit = memDC.SelectObject(&MemBitmap);

    CBrush memBrush;
    memBrush.CreateSolidBrush(::GetSysColor(COLOR_3DFACE));

    HGDIOBJ hOld;
    hOld = memDC.SelectObject(&memBrush);
    memDC.SelectObject(GetStockObject(NULL_PEN));
    memDC.Rectangle(&rectClient);
    memDC.DrawEdge(&rectClient, BDR_RAISED, BF_RECT);

    memDC.SetBkMode(TRANSPARENT);
    CRect GraphRect;
    GraphRect.left = rectClient.left + 20;
    GraphRect.right = rectClient.right - 20;   
    GraphRect.top = rectClient.top + 20;
    GraphRect.bottom = rectClient.bottom - 20;
    memDC.Rectangle(GraphRect);

   

    memDC.SelectObject(&m_fontHor);
    CSize sizeText = memDC.GetOutputTextExtent("aa");
    int iX = sizeText.cx,  iY = sizeText.cy;

    memDC.SelectObject(&m_fontTitle);
    memDC.SetTextAlign(TA_CENTER);

    if (g_pDoc->m_StatisticLedDataContainer.IsAllStatisticPara(FALSE)  && m_para.GetTotalNum() > 0)
    {
        memDC.TextOutA((GraphRect.left + GraphRect.right) / 2,  GraphRect.top, m_strTitle);
    }
    else
    {
        memDC.TextOutA((GraphRect.left + GraphRect.right) / 2,  GraphRect.top, "区间分布(示例)");
    }

    memDC.SelectObject(&m_fontHor);
    CRect DrawRect;
    DrawRect.left =  GraphRect.left + 2 * iX;
    DrawRect.right =  GraphRect.right - 2 * iX;
    DrawRect.top =  GraphRect.top + 3 * iY;
    DrawRect.bottom =  GraphRect.bottom - iY;
    
    CPen PenLine;
    PenLine.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    memDC.SelectObject(&PenLine);
    memDC.MoveTo(DrawRect.left, DrawRect.top);
    memDC.LineTo(DrawRect.left, DrawRect.bottom);
    memDC.MoveTo(DrawRect.left, DrawRect.bottom);
    memDC.LineTo(DrawRect.right, DrawRect.bottom);
    memDC.SelectObject(&m_fontHor);    
    int iCurXpos, iCurYpos, iRangeXPos;
    for (int i = 0; i < 6; i ++)
    {
        iCurYpos = DrawRect.top + DrawRect.Height() / 5 * i;
        memDC.MoveTo(DrawRect.left - iX / 4, iCurYpos);
        memDC.LineTo(DrawRect.left, iCurYpos);
        CString strTemp;
        strTemp.Format("%.1f", (5 - i) * 1.0f / 5);
        iCurYpos -= iY / 2;
        memDC.TextOutA(DrawRect.left - 2 * iX, iCurYpos, strTemp);
    }
    memDC.SelectObject(&m_fontHor);
    CArray<int, int>m_ArrayPos;
    for (int i = 0; i < 7; i ++)
    {
        iCurXpos = DrawRect.left + DrawRect.Width() / 6 * i;
        memDC.MoveTo(iCurXpos, DrawRect.bottom);
        memDC.LineTo(iCurXpos, DrawRect.bottom + iY / 4);
        m_ArrayPos.Add(iCurXpos);
    }  
    if (g_pDoc->m_StatisticLedDataContainer.IsAllStatisticPara(FALSE) && m_para.GetTotalNum() > 0)
    {
        for (int i = 0; i < DISTRIBUTION_NUM; i++)
        {
            iCurXpos = (m_ArrayPos.GetAt(i) + m_ArrayPos.GetAt(i + 1)) / 2; 
            iRangeXPos = (m_ArrayPos.GetAt(i + 1) - m_ArrayPos.GetAt(i));
            memDC.TextOutA(iCurXpos, DrawRect.bottom + iY / 2, g_pDoc->m_StatisticLedDataContainer.GetEveryDistributionName(i));
            CRect rectColumn;
            rectColumn.left = iCurXpos - iRangeXPos / 4;
            rectColumn.right = iCurXpos + iRangeXPos / 4;
            iCurYpos = (int)(DrawRect.Height() * m_para.fEveryDistributionPer[i] / 100);
            rectColumn.top = DrawRect.bottom - iCurYpos;
            rectColumn.bottom = DrawRect.bottom;
            CBrush brushTemp;
            brushTemp.CreateSolidBrush(m_AllColor[i]);
            memDC.SelectObject(&brushTemp);
            memDC.Rectangle(rectColumn);
            CString strTemp;
            strTemp.Format("%.2f%%(个数%d)",
                m_para.fEveryDistributionPer[i], m_para.iEveryDistributionNum[i]);
            memDC.TextOutA(iCurXpos, DrawRect.bottom - iCurYpos - iY, strTemp);
        }
    }
    else
    {
        for (int i = 0; i < DISTRIBUTION_NUM; i++)
        {
            iCurXpos = (m_ArrayPos.GetAt(i) + m_ArrayPos.GetAt(i + 1)) / 2; 
            iRangeXPos = (m_ArrayPos.GetAt(i + 1) - m_ArrayPos.GetAt(i));
            memDC.TextOutA(iCurXpos, DrawRect.bottom + iY / 2, g_pDoc->m_StatisticLedDataContainer.GetEveryDistributionName(i));
            CRect rectColumn;
            rectColumn.left = iCurXpos - iRangeXPos / 4;
            rectColumn.right = iCurXpos + iRangeXPos / 4;
            iCurYpos = DrawRect.Height() * 20 / 100;
            rectColumn.top = DrawRect.bottom - iCurYpos;
            rectColumn.bottom = DrawRect.bottom;
            CBrush brushTemp;
            brushTemp.CreateSolidBrush(m_AllColor[i]);
            memDC.SelectObject(&brushTemp);
            memDC.Rectangle(rectColumn);
            CString strTemp;
            strTemp.Format("%.2f%%(个数%d)",
                16.67f , 20);
            memDC.TextOutA(iCurXpos, DrawRect.bottom - iCurYpos - iY, strTemp);
        }
    }    


    memDC.SelectObject(hOld);

    dc.BitBlt(0, 0, rectClient.Width(), rectClient.Height(), &memDC, 0, 0, SRCCOPY);
    MemBitmap.DeleteObject();
    memDC.DeleteDC();
}
