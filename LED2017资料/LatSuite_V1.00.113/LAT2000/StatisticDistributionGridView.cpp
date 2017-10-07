GetStackSize
// StatisticDistributionGridView.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "StatisticDistributionGridView.h"
#include "LAT2000Doc.h"


// CStatisticDistributionGridView

IMPLEMENT_DYNCREATE(CStatisticDistributionGridView, CFormView)

CStatisticDistributionGridView::CStatisticDistributionGridView()
	: CFormView(CStatisticDistributionGridView::IDD)
{

}

CStatisticDistributionGridView::~CStatisticDistributionGridView()
{
}

void CStatisticDistributionGridView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_GRID_STATISTIC_DISTRIBUTION, m_cStatisticDistributeGrid);
    DDX_Control(pDX, IDC_IPIECHARTX1, m_PieChart);
    DDX_Control(pDX, IDC_RECT1, m_cRect1);
    DDX_Control(pDX, IDC_RECT2, m_cRect2);
}

BEGIN_MESSAGE_MAP(CStatisticDistributionGridView, CFormView)
    ON_WM_SIZE()
    ON_MESSAGE(MSG_STATISTIC_DIS_GRID_RELIST_DATA, &CStatisticDistributionGridView::OnMsgStatisticDistributionGridRelistData)
    ON_WM_TIMER()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CStatisticDistributionGridView 诊断

#ifdef _DEBUG
void CStatisticDistributionGridView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStatisticDistributionGridView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStatisticDistributionGridView 消息处理程序


void CStatisticDistributionGridView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();

    // TODO: 在此添加专用代码和/或调用基类
    if (NULL != g_pDoc)
    {
        g_pDoc->m_hWndStatisticDisbuteGridView = m_hWnd;
        g_pDoc->m_StatisticLedDataContainer.ListStatisticDistributeData(m_cStatisticDistributeGrid);

    }
}


void CStatisticDistributionGridView::OnSize(UINT nType, int cx, int cy)
{
    CFormView::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    if (!IsWindow(m_cStatisticDistributeGrid.GetSafeHwnd()))
    {
        return;
    }

    m_cStatisticDistributeGrid.ShowWindow(SW_HIDE);
    CRect rect;
    GetClientRect(&rect);
    CRect RectTemp, RectTemp2; 
    RectTemp = rect;
    RectTemp.right = rect.Width() / 3;
    RectTemp.bottom = rect.Height() / 2;
    m_cRect1.MoveWindow(RectTemp);
    

    if (RectTemp.Width() > RectTemp.Height() * 4 / 2)
    {
        RectTemp2.top = RectTemp.top + 1;
        RectTemp2.bottom= RectTemp.bottom - 1;
        RectTemp2.left = (RectTemp.left + RectTemp.right) / 2 - RectTemp2.Height() * 4 / 2 / 2;
        RectTemp2.right = (RectTemp.left + RectTemp.right) / 2 + RectTemp2.Height() * 4 / 2 / 2;
    }
    else
    {
        RectTemp2.left = RectTemp.left + 1;
        RectTemp2.right= RectTemp.right - 1;
        RectTemp2.top = (RectTemp.top + RectTemp.bottom) / 2 - RectTemp2.Width() * 2 / 4 / 2;
        RectTemp2.bottom = (RectTemp.top + RectTemp.bottom) / 2 + RectTemp2.Width() * 2 / 4 / 2;
    }
    m_PieChart.MoveWindow(&RectTemp2);
    RectTemp = rect;
    RectTemp.left = rect.Width() / 3 + 1;
    RectTemp.bottom = rect.Height() / 2;
    m_cRect2.MoveWindow(RectTemp);
    if (RectTemp.Width() > RectTemp.Height() * 2)
    {
        RectTemp2.top = RectTemp.top;
        RectTemp2.bottom= RectTemp.bottom;
        RectTemp2.left = (RectTemp.left + RectTemp.right) / 2 - RectTemp.Height() * 2 / 2;
        RectTemp2.right = (RectTemp.left + RectTemp.right) / 2 + RectTemp.Height() * 2 / 2;
    }
    else
    {
        RectTemp2.left = RectTemp.left;
        RectTemp2.right= RectTemp.right;
        RectTemp2.top = (RectTemp.top + RectTemp.bottom) / 2 - RectTemp.Width() / 2 / 2;
        RectTemp2.bottom = (RectTemp.top + RectTemp.bottom) / 2 + RectTemp.Width()  / 2 / 2;
    }
    RectTemp = rect;
    RectTemp.top = rect.Height() / 2 + 2;
    m_cStatisticDistributeGrid.MoveWindow(&RectTemp);
    m_cStatisticDistributeGrid.ShowWindow(SW_SHOW);
}
BEGIN_EVENTSINK_MAP(CStatisticDistributionGridView, CFormView)
    ON_EVENT(CStatisticDistributionGridView, IDC_GRID_STATISTIC_DISTRIBUTION, 29, CStatisticDistributionGridView::OwnerDrawCellGridStatisticDistribution, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PBOOL)
    ON_EVENT(CStatisticDistributionGridView, IDC_GRID_STATISTIC_DISTRIBUTION, 23, CStatisticDistributionGridView::RowColChangeGridStatisticDistribution, VTS_I4 VTS_I4)
    ON_EVENT(CStatisticDistributionGridView, IDC_GRID_STATISTIC_DISTRIBUTION, 12, CStatisticDistributionGridView::GetCellTextGridStatisticDistribution, VTS_I4 VTS_I4 VTS_PBSTR VTS_PBOOL)
END_EVENTSINK_MAP()

void CStatisticDistributionGridView::OwnerDrawCellGridStatisticDistribution(long Row, long Col, long hdc, long Left, long Top, long Right, long Bottom, BOOL* Handled)
{
    // TODO: 在此处添加消息处理程序代码
    CDC * pDc = CDC::FromHandle((HDC)hdc);
    pDc->SetTextAlign(TA_CENTER);   
    pDc->SetTextColor(RGB(0, 0, 0));
    CBrush brush;
    brush.CreateSolidBrush(RGB(255, 255, 255));
    if (0)
    {
        // 自己画图
        CRect drect(Left, Top, Right, Bottom);
        pDc->FillRect(drect, &brush);
        CBitmap	m_ImagePrint;
        m_ImagePrint.LoadBitmap(IDB_L_2THETA + Col - 1);
        BITMAP bm;
        m_ImagePrint.GetBitmap(&bm);
        CDC dcImange;
        dcImange.CreateCompatibleDC(pDc);
        dcImange.SelectObject(m_ImagePrint);
      	pDc->BitBlt(Left, Top, Left + bm.bmWidth,Top + bm.bmHeight,&dcImange,0,0,SRCCOPY);

    }

    CString strTemp;   
    TEXTMETRIC  tm;
    int iFontH,iFontW;
    pDc->GetTextMetrics(&tm);
    iFontH = tm.tmHeight + tm.tmExternalLeading;
    iFontW = tm.tmAveCharWidth;
    pDc->SetTextAlign(TA_CENTER);
    strTemp = g_pDoc->m_StatisticLedDataContainer.GetStatisticDistributeItemText(Row, Col);
    pDc->TextOutA((Left + Right) / 2, (Top + Bottom) / 2  - iFontH / 2, strTemp);

    *Handled = TRUE;
}


void CStatisticDistributionGridView::RowColChangeGridStatisticDistribution(long Row, long Col)
{
    // TODO: 在此处添加消息处理程序代码  
       m_cRect2.m_strTitle =  g_pDoc->m_StatisticLedDataContainer.GetStatisticParaName(g_pDoc->m_StatisticLedDataContainer.GetCurSelStatisticPara(Row - 1).iIndex, 0) + " 区间分布";
       m_cRect2.m_para = g_pDoc->m_StatisticLedDataContainer.GetCurSelStatisticPara(Row - 1);
       m_cRect2.Invalidate(TRUE);
}


afx_msg LRESULT CStatisticDistributionGridView::OnMsgStatisticDistributionGridRelistData(WPARAM wp, LPARAM lp)
{
    SetTimer(2, 100, NULL);
    return 0;
}


void CStatisticDistributionGridView::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if (2 == nIDEvent)
    {
        BeginWaitCursor();
        if (g_pDoc->m_StatisticLedDataContainer.IsAllStatisticPara(FALSE))
        {
            m_PieChart.SetItemValue(0, g_pDoc->m_StatisticLedDataContainer.GetQLEDNumPer());
            m_PieChart.SetItemValue(1, g_pDoc->m_StatisticLedDataContainer.GetUnQLEDNumPer());
            m_PieChart.SetItemValue(2, g_pDoc->m_StatisticLedDataContainer.GetUnONLEDNumPer()); 
            CString strTemp;		
            strTemp.Format("合格:%d(%.2f%%)", g_pDoc->m_StatisticLedDataContainer.GetQLEDNum(), 
                g_pDoc->m_StatisticLedDataContainer.GetQLEDNumPer());
            m_PieChart.SetItemTitle(0, strTemp);

            strTemp.Format("不合格(超限值):%d(%.2f%%)", g_pDoc->m_StatisticLedDataContainer.GetUnQLEDNum(), 
                g_pDoc->m_StatisticLedDataContainer.GetUnQLEDNumPer());
            m_PieChart.SetItemTitle(1, strTemp);

            strTemp.Format("不合格(未亮或无灯):%d(%.2f%%)", g_pDoc->m_StatisticLedDataContainer.GetUnONLEDNum(), 
                g_pDoc->m_StatisticLedDataContainer.GetUnONLEDNumPer());
            m_PieChart.SetItemTitle(2, strTemp);
        }
        g_pDoc->m_StatisticLedDataContainer.ListStatisticDistributeData(m_cStatisticDistributeGrid);
        EndWaitCursor();
    }

    KillTimer(nIDEvent);

    CFormView::OnTimer(nIDEvent);
}


BOOL CStatisticDistributionGridView::OnEraseBkgnd(CDC* pDC)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    return CFormView::OnEraseBkgnd(pDC);
}


void CStatisticDistributionGridView::GetCellTextGridStatisticDistribution(long Row, long Col, BSTR* Text, BOOL* Changed)
{
    // TODO: 在此处添加消息处理程序代码
    if (NULL == g_pDoc)
    {
        return;
    }
    if (Row >= 0 && Col >= 0)
    {
        * Text = g_pDoc->m_StatisticLedDataContainer.GetStatisticDistributeItemText(Row, Col).AllocSysString();;
        * Changed = TRUE;
    }
}
